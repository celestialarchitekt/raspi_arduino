import time
from picamera2 import Picamera2
print(Picamera2.global_camera_info())
picam2 = Picamera2(camera_num=0)
picam2.configure(picam2.create_still_configuration(main={"size": (1280, 720)}))
picam2.start()
time.sleep(2)

image = "/home/megatron/testImage.jpg"
picam2.capture_file(image)

