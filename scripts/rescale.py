import os, sys

from shutil import rmtree
import shared

rescaling_name = "rescale"
rescaling_command = "{binary} {input_dir} {output_dir} {opts}"

def rescale(raw_dir, output_dir, options="-t 3 -w 100 -p ", horizon_file=""):
  top_dir = os.path.dirname(raw_dir)
  shared.mkdir_graceful( output_dir )
  rescaling_bin = os.path.join(shared.repo_dir, shared.bin_dir, rescaling_name)
  if horizon_file:
    options += " -i " + horizon_file
  cmd = rescaling_command.format(binary=rescaling_bin, input_dir=raw_dir, output_dir=output_dir, opts=options)
  print cmd
  os.system( cmd )

def main():
    if len(sys.argv) < 3:
        print "Usage: {0} <top_dir> <vid_name>".format(sys.argv[0])
        sys.exit()

    top_dir = sys.argv[1]
    video_name = sys.argv[2]

    # TODO: Read in rescaling options from config

    from make_video import convert_to_video

    for dir_name, subdirList, fileList in os.walk(top_dir):
        if dir_name.endswith('raw'):
            parent_dir = os.path.dirname(dir_name)
            horizon_file = os.path.join(parent_dir, "imuLog.txt")

            output_dir = os.path.join(parent_dir, "tmp")
            rescale(dir_name, output_dir, options=options, horizon_file=horizon_file)
            
            video_file = os.path.join(parent_dir, video_name)
            convert_to_video( output_dir, video_file)
            # rmtree(output_dir)


if __name__ == "__main__":
    main()
