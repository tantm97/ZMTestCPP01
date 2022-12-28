import numpy as np 
import cv2 


def main():
    n_images = 10
    width = 800
    height = 600

    # Read to buffer
    buffer = np.fromfile("data/data.bin", dtype=np.uint8)

    # Reshape the buffer
    buffer = buffer.reshape(n_images, height, width)

    # Threshold the buffer to find exclusive mutual objects as foreground
    thresh = (buffer>0).astype(np.uint8)

    # Read the result
    with open('data/results.txt', 'r') as f:
        lines = f.readlines()

    # Convert image to rgb and draw image
    for n in range(n_images):
        rgb = cv2.cvtColor(buffer[n,:,:], cv2.COLOR_GRAY2RGB)
        coords = lines[n].replace('(', '').replace(')', '').replace(',', '').replace('\n', '').split(' ')
        for i in range(int(len(coords) / 4)):
            coord = [int(c) for c in coords[4*i:4*i+4]]
            cv2.rectangle(rgb, (coord[1], coord[0]), (coord[1] + coord[3], coord[0] + coord[2]), (255, 255, 255), 1)
        cv2.imwrite(f"data/visualize/{n}.png", rgb)


if __name__ == "__main__":
    main()