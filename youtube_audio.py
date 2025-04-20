from pytubefix import YouTube
from pydub import AudioSegment
import os

def download_audio(youtube_url, output_path="."):
    try:
        # Create YouTube object
        yt = YouTube(youtube_url)
        
        # Get the audio stream with the highest quality
        audio_stream = yt.streams.filter(only_audio=True).first()
        
        if audio_stream:
            print(f"Downloading audio from: {yt.title}")
            # Download the audio stream; this returns the path of the downloaded file.
            downloaded_file = audio_stream.download(output_path)
            print(f"Audio downloaded successfully to: {downloaded_file}")
            
            # Extract the base filename without extension
            file_root, file_ext = os.path.splitext(downloaded_file)
            
            # pydub requires the format of the file; we use file_ext without the dot
            input_format = file_ext[1:] if file_ext.startswith('.') else file_ext
            
            # Load the audio file using pydub
            audio = AudioSegment.from_file(downloaded_file, format=input_format)
            
            # Define the output filename with .mp3 extension
            mp3_filename = file_root + ".mp3"
            
            # Export the audio to MP3
            audio.export(mp3_filename, format="mp3")
            print(f"Audio converted to MP3 and saved as: {mp3_filename}")
            
            # Optionally, remove the original downloaded file if no longer needed
            os.remove(downloaded_file)
            print(f"Removed temporary file: {downloaded_file}")
        else:
            print("No audio stream found.")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    youtube_url = input("Enter the YouTube URL: ")
    output_path = input("Enter the output path (default is current directory): ") or "."
    download_audio(youtube_url, output_path)
