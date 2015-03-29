import os, sys

def convert_to_video(top_dir, raw_dir):
    temp_dir = raw_dir
#    temp_dir = top_dir + "/tmp"
#    os.mkdir(temp_dir)
#    num_files = len(os.listdir(raw_dir))
#    os.system(exec_dir + "/16to8/build/16to8 " + raw_dir + " " + temp_dir + " " + str(num_files))
 #   print exec_dir + "/16to8/build/16to8 " + raw_dir + " " + temp_dir + " " + str(num_files)
    os.system("ffmpeg -i \"" + temp_dir + "/img_%06d.png\" -r 24 -vf \"transpose=2\" " + top_dir + "/out.avi")
    #  rmtree(temp_dir)
    
convert_to_video('.', sys.argv[1])
