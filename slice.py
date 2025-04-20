from pydub import AudioSegment
import os
import math

def split_audio_by_size(input_file, target_size_mb, output_format="mp3"):
    audio = AudioSegment.from_file(input_file)
    total_size = os.path.getsize(input_file) / (1024 * 1024)  # Convert to MB
    duration_ms = len(audio)  # Total duration in milliseconds
    target_duration_ms = math.ceil((target_size_mb / total_size) * duration_ms)
    
    num_parts = math.ceil(total_size / target_size_mb)
    output_base = os.path.splitext(input_file)[0]  # Get base name
    
    for i in range(num_parts):
        start_time = i * target_duration_ms
        end_time = min((i + 1) * target_duration_ms, duration_ms)
        
        chunk = audio[start_time:end_time]
        output_filename = f"{output_base}_part{i+1}.{output_format}"
        
        chunk.export(output_filename, format=output_format)
        print(f"Saved {output_filename}")

    print("Splitting complete.")

if __name__ == "__main__":
    input_audio = "./audio/sad.mp3"  
    target_size = 3.75  # MB
    split_audio_by_size(input_audio, target_size)
