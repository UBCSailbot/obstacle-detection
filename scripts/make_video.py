import os, sys
from shutil import rmtree

def run_16to8(repo_dir, raw_dir, tmp_dir):
    executable = os.path.join(repo_dir, "16to8", "build", "16to8")
    num_files = str( len(os.listdir(raw_dir)) )
    os.mkdir(tmp_dir)
    os.system(executable + " " + raw_dir + " " + tmp_dir + " " + num_files)  

def convert_to_video(repo_dir, top_dir, raw_dir, rotate=False, fps=27):
    tmp_dir = os.path.join(top_dir, "tmp")
    run_16to8(repo_dir, raw_dir, tmp_dir)
    rotation = ""
    if rotate:
       rotation = "-vf \"transpose=2\" "
    os.system("ffmpeg -i \"" + os.path.join(tmp_dir, "img_%06d.png") + \
        "\" -r " + str(fps) + " " +  rotation + os.path.join(top_dir, "out.avi"))
    rmtree(tmp_dir)

if __name__ == "__main__":
    convert_to_video(sys.argv[1], sys.argv[2], sys.argv[3])
