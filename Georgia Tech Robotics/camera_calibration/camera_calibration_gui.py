# Copyright 2021 by Georgia Tech. All rights reserved.
# Author: Ari Nachison

# Description:
# This file creates a GUI designed to be used for running Aquatics Robotics localization scripts.

import tkinter as tk
from tkinter import ttk, filedialog
import camera_calibration, os
import sys

def ChangeFileExtension(file_path, new_extension):
    file_name, ext = os.path.splitext(file_path)
    return file_name + new_extension


# References https://docs.python.org/3/library/tkinter.html
class Application(tk.Frame):
    def __init__(self, master=None):
        super().__init__(master)
        self.master = master
        self.create_items()

    def SetHeightAndWidth(self):
        # Contain integer values, in pixesl.
        self.width = 490
        self.height = 150

        # Set initial window size, in pixels, width x height
        self.master.geometry(str(self.width) + "x" + str(self.height)) 

    def AddProcessVideoRow(self):
        # This processes a video by identifying aruco tags in each frame.
        # The processing creates a pkl file containg identified tag information.
        #TODO update the description here
        y=5
        row = 0
        self.process_video_label = tk.Label(text = "Video File Path:")
        self.process_video_label.grid(row=row,column=0)

        self.process_video_entry_box = tk.Entry()
        self.process_video_entry_box.grid(row=row, column=1)

        self.video_entry_browse = tk.Button(text = "Browse", command = self.browse_for_video)
        self.video_entry_browse.grid(row=row, column=2)

        row += 1
        self.square_side_label= tk.Label(text = "Square Side Length (meters):")
        self.square_side_label.grid(row=row, column=0)

        self.square_side_entry = tk.Entry()
        self.square_side_entry.grid(row=row, column=1)

        row += 1
        self.process_video_label = tk.Label(text = "(optional, default is 100) Resize Percent (1-100):")
        self.process_video_label.grid(row=row, column=0)

        self.resize_entry = tk.Entry()
        self.resize_entry.grid(row=row, column=1)

        row += 1
        self.camera_name_label = tk.Label(text = "(optional) Camera Name:")
        self.camera_name_label.grid(row=row, column=0)

        self.camera_name_entry = tk.Entry()
        self.camera_name_entry.grid(row=row, column=1)
        
        row += 1
        self.process_video_button = tk.Button(text= "Process Video", bg="green", command=self.ProcessVideo)
        self.process_video_button.grid(row=row, column=1)

        self.exit_button = tk.Button(text= "Exit", bg="red", command=self.master.destroy)
        self.exit_button.grid(row=row, column=0)

    def browse_for_video(self):
        file_path = filedialog.askopenfilename(parent = self.master, title = "Choose Video File")
        self.process_video_entry_box.delete(0, 'end')
        self.process_video_entry_box.insert(0, file_path)

    def ProcessVideo(self):
        file_path = self.process_video_entry_box.get()
        if not os.path.exists(file_path):
            sys.exit("Error: File does not exist")
        resizePercent = 100
        try:
            resizePercent = int(self.resize_entry.get())
        except:
            print('Error: Resize percent needs to be integer')
            return
        try:
            squareSideMeters = float(self.square_side_entry.get())
        except:
            print('Error: square side length must be float')
            return
        camera_name = self.camera_name_entry.get()
        if(camera_name != None and camera_name == ""):
            camera_name = None
        camera_calibration.calibrateCameraFromVideo(file_path, squareSideMeters, resizePercent, camera_name)

    def create_items(self):
        self.SetHeightAndWidth()
        self.master.title('uNet - Camera Calibration')

        self.AddProcessVideoRow()
        return


def main():
    root = tk.Tk()
    app = Application(master=root)
    app.mainloop()

if __name__ == "__main__":
    main()