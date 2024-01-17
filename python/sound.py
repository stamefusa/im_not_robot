from pygame import mixer
import time

def play_sound(file_path):
    mixer.init()
    mixer.music.load(file_path)
    mixer.music.play()

def main():
    sound_file = "imnotrobot.mp3"
    play_sound(sound_file)
    time.sleep(10)

if __name__ == '__main__':
    main()