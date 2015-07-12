import os

script_dir = "scripts"
rigRunner_target = "rigRunner"

def build_rigRunner(repo_dir):
    build_dir = os.path.join(repo_dir, "build")
    os.system( "mkdir {0}".format(build_dir) )
    os.chdir( build_dir )
    os.system( "cmake .." )
    os.system( "make rigRunner" )
