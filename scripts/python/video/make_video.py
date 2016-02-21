import os, sys
from shutil import rmtree
import __init__
from shared import mkdir_graceful

def convert_to_video(frame_dir, video_file, frame_rate=27, rotate=False):
  rotate_str = ""
  if rotate:
    rotate_str = "-vf \"transpose=2\""

  cmd_str = "ffmpeg -r {fps} -i \"{input}\" {transform} {output}"\
    .format(input=os.path.join(frame_dir, "img_%06d.png"), \
            fps=frame_rate,\
            transform=rotate_str,
            output=video_file
            )
  print "Converting frames to video:"
  print cmd_str
  os.system( cmd_str )

if __name__ == "__main__":
    if len(sys.argv) == 4:
        convert_to_video(sys.argv[1], sys.argv[2], frame_rate=int(sys.argv[3]))
    elif len(sys.argv) == 3:
        convert_to_video(sys.argv[1], sys.argv[2])
    else:
        print "Usage: {0} <frame_dir> <video_file> [frame_rate]".format(sys.argv[0])
