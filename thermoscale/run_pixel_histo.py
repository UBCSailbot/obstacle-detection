import os
import pixel_histo as ph

top_dir = "/home/paul/sailbot/expt/fluctus/data"
overwrite_existing = False

for cur_dir, dirnames, f in os.walk(top_dir):
	if cur_dir.endswith("raw"):
		ph.generate_video_histo(cur_dir, overwrite_existing)
