#! /usr/bin/python

import sys
from os import path, system
import argparse

import numpy as np
import cv2

"""
Evaluate the performance of a horizon line detector.
"""

def main(argv):
    if argv is None:
        argv = sys.argv[1:]

    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('binary', help='Path to executable file to use to compute horizon metrics. Should have argument order [exec] [imu-file] [gt-file] [output-file], where [output-file] is formatted to have one frame number and one score per line.')
    parser.add_argument('gt_file_list', help='Text file where each line gives the path to a ground truth horizone line file')
    parser.add_argument('--imu-file-name', default='imuLog_adjusted.txt', help='Name (not full path) of the file containing raw IMU data. This file is assumed to lie in the same directory as the ground truth file.')
    parser.add_argument('-m', '--metrics-file-name', default="horizon_eval.txt", help='the name of the output file to produce containing evaluation metrics for the accuracy of horizon detection')
    parser.add_argument('-a', '--aggregated-metrics-file', required=True, help='Path of the file to which to write aggregated metrics for the entire dataset.')
    parser.add_argument('-w', '--overwrite-existing', action='store_true', help='If set, this flag tells the program to overwrite any existing output files')

    args = parser.parse_args()

    all_scores = []

    with open(args.gt_file_list) as gt_list_fd, open(args.aggregated_metrics_file, 'w') as agg_fd:
        
            for gt_file in gt_list_fd.readlines():
                
                # remove newlines and any other padding whitespace
                gt_file = gt_file.strip()

                # skip empty lines
                if not gt_file:
                    continue

                # initialize paths
                parent_dir = path.dirname(gt_file)
                imu_file_path = path.join(parent_dir, args.imu_file_name)
                metrics_file_path = path.join(parent_dir, args.metrics_file_name)

                # generate the metrics file for current ground-truth file
                if args.overwrite_existing or not path.exists(metrics_file_path):
                    cmd = ' '.join([args.binary, imu_file_path, gt_file, metrics_file_path])
                    print "Now executing command: " + cmd
                    system(cmd)

                # read scores from metrics file
                with open(metrics_file_path, 'r') as metrics_fd:
                    for line in metrics_fd.readlines():
                        # parse score from line of text
                        cur_score_str = line.split()[1]
                        cur_score = float(cur_score_str)
                        # append score to list
                        all_scores.append(cur_score)
                        # write score to the aggregated metrics file
                        agg_fd.write(cur_score_str + '\n')

    # Calculate the average of all scores
    all_scores_np = np.array(all_scores)
    avg_score = np.mean(all_scores)
    print '================'
    print 'Average horizon accuracy: ' + str(avg_score)
    print '(total frames considered: ' + str(len(all_scores)) + ')'
    print '================'

if __name__ == "__main__":
   main(sys.argv[1:])
