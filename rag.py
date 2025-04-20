import os
import re
import shutil

import gradio as gr
from langchain_chroma import Chroma
from langchain_community.document_loaders import TextLoader
from langchain_community.embeddings import HuggingFaceEmbeddings, OllamaEmbeddings
from langchain_ollama import ChatOllama
from langchain.memory import ConversationBufferMemory
from langchain.chains import ConversationalRetrievalChain
from langchain_text_splitters import RecursiveCharacterTextSplitter

# Define constants
DOCUMENT_PATH = "./transcription.txt"
DB_NAME = "vector_db"
MODEL = "gemma3:4b"

def trim_start_end(input_string):
    return re.sub(r"^[0-9\s:.]+|[0-9\s:.]+$", "", input_string)

def load_document(document_path):
    loader = TextLoader(document_path)
    documents = loader.load()
    for doc in documents:
        doc.metadata["doc_type"] = "single_document"
        doc.metadata["filename"] = os.path.basename(document_path)
    return documents

def split_documents(documents):
    text_splitter = RecursiveCharacterTextSplitter(
        chunk_size=500,  # Adjust chunk size as needed
        chunk_overlap=50,  # Adjust chunk overlap as needed
        length_function=len,
        separators=["\n\n", "\n", ". ", " ", ""]
    )
    chunks = text_splitter.split_documents(documents)
    print(f"Total number of chunks: {len(chunks)}")
    return chunks

def create_vectorstore(chunks):
    # embeddings = HuggingFaceEmbeddings(temperature=0.7, model_name="sentence-transformers/all-mpnet-base-v2")
    embeddings = OllamaEmbeddings(temperature=0.7,model="nomic-embed-text")
    if os.path.exists(DB_NAME):
        shutil.rmtree(DB_NAME)
    vectorstore = Chroma.from_documents(
        documents=chunks, embedding=embeddings, persist_directory=DB_NAME
    )
    print(f"Vectorstore created with {vectorstore._collection.count()} documents")
    return vectorstore

def create_conversation_chain(vectorstore):
    llm = ChatOllama(temperature=0.7, model=MODEL)
    memory = ConversationBufferMemory(memory_key="chat_history", return_messages=True)
    retriever = vectorstore.as_retriever()
    conversation_chain = ConversationalRetrievalChain.from_llm(
        llm=llm, retriever=retriever, memory=memory
    )
    return conversation_chain

def setup_rag_system(document_path=DOCUMENT_PATH):
    documents = load_document(document_path)
    chunks = split_documents(documents)
    vectorstore = create_vectorstore(chunks)
    conversation_chain = create_conversation_chain(vectorstore)
    return conversation_chain

def chat(question, history, conversation_chain):
    result = conversation_chain.invoke({"question": question})
    return result["answer"]

def launch_chat_interface(document_path=DOCUMENT_PATH):
    conversation_chain = setup_rag_system(document_path)

    def chat_wrapper(question, history):
        return chat(question, history, conversation_chain)

    interface = gr.ChatInterface(
        chat_wrapper,
        title=f"Document Q&A: {os.path.basename(document_path)}",
        description="Ask questions about the document content",
        type="messages",
    ).launch(inbrowser=True)
    return interface

if __name__ == "__main__":
    import sys
    if len(sys.argv) > 1:
        doc_path = sys.argv[1]
        launch_chat_interface(doc_path)
    else:
        launch_chat_interface()