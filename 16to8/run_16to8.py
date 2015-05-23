import os

top_dir = "/home/paul/sailbot/expt/vigil/data"
exec_path = "/home/paul/sailbot/code/obstacle-avoidance/16to8/build/16to8"
overwrite_existing = False

def rreplace(s, old, new, occurrence):
    li = s.rsplit(old, occurrence)
    return new.join(li)
    
def make_video(tmp_dir, fps=27, rotate=False):
    rotation = ""
    if rotate:
       rotation = "-vf \"transpose=2\" "
    os.system("ffmpeg -i \"" + os.path.join(tmp_dir, "img_%06d.png") + \
        "\" -r " + str(fps) + " " +  rotation + \
        os.path.join(tmp_dir, '..', "out_modal100.avi") )
    

def generate_rescaled_frames(exec_path, input_dir, output_dir, overwrite_existing=True):
    if overwrite_existing or not os.path.exists(output_dir): 
        num_files = len( os.listdir(input_dir) )
        os.mkdir(output_dir)
        os.system( ' '.join([exec_path, input_dir, output_dir, str(num_files)] ) )

for cur_dir, dirnames, f in os.walk(top_dir):
	if cur_dir.endswith("raw"):
	    tmp_dir = rreplace(cur_dir, "raw", "tmp_modal100", 1)
	    generate_rescaled_frames(exec_path, cur_dir, tmp_dir, overwrite_existing)
	    make_video(tmp_dir, 24, True)
		
		
	
