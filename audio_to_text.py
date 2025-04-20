import whisper

def transcribe_audio(file_path):
    model = whisper.load_model("base")  # Choose from: tiny, base, small, medium, large
    result = model.transcribe(file_path)
    return result["text"]

# Example usage
audio_file = "playback.mp3"  # Change to your file
transcription = transcribe_audio(audio_file)
with open("transcription.txt", "w") as f:
    f.write(transcription)
    print("Transcription:", transcription)
