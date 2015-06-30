import os, sys
from shutil import rmtree
from support import mkdir_graceful

bin_dir = "build"
rescaling_name = "rescale"
rescaling_command = "{binary} {input_dir} {output_dir} {opts}"

def rescale(repo_dir, raw_dir, output_dir="", options="-t 3 -w 100 -p ", horizon_file=""):
  top_dir = os.path.dirname(raw_dir)
  if not output_dir:
    output_dir = os.path.join(top_dir, "tmp")
  mkdir_graceful( output_dir )
  rescaling_bin = os.path.join(repo_dir, bin_dir, rescaling_name)
  if horizon_file:
    options += " -i " + horizon_file
  cmd = rescaling_command.format(binary=rescaling_bin, input_dir=raw_dir, output_dir=output_dir, opts=options)
  print cmd
  os.system( cmd )
  

def convert_to_video(frame_dir, video_name="out.avi", frame_rate=24, rotate=False):
  top_dir = os.path.dirname(frame_dir)
  rotate_str = ""
  if rotate:
    rotate_str = "-vf \"transpose=2\""

  cmd_str = "ffmpeg -i \"{input}\" -r {fps} {transform} {output}"\
    .format(input=os.path.join(frame_dir, "img_%06d.png"), \
            fps=frame_rate,\
            transform=rotate_str,
            output=os.path.join(top_dir, video_name)
            )
  print cmd_str
  os.system( cmd_str )

if __name__ == "__main__":
    convert_to_video(sys.argv[1], sys.argv[2], sys.argv[3])
