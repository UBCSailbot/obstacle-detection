import os, sys
from make_video import rescale, convert_to_video
from shutil import rmtree

repo_dir = "/home/paul/sailbot/code/obstacle-avoidance/build"

options = "-t 2 -w 100 -p --invert-pitch"
video_name = "mode100.avi"

def main():
	if len(sys.argv) < 3:
		print "Usage: {0} <top_dir> <repo_dir>".format(sys.argv[0])
		sys.exit()
		
	top_dir = sys.argv[1]
	repo_dir = sys.argv[2]

	for dir_name, subdirList, fileList in os.walk(top_dir):
		if dir_name.endswith('raw'):
			parent_dir = os.path.dirname(dir_name)
			horizon_file = os.path.join(parent_dir, "imuLog.txt")
			
			output_dir = os.path.join(parent_dir, "tmp")
			rescale(repo_dir, dir_name, options=options, horizon_file=horizon_file)
			convert_to_video( output_dir, video_name=video_name)
			# rmtree(output_dir)


if __name__ == "__main__":
    main()
