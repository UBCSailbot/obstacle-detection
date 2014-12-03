def read_file_list(file_list):
    text = open(file_list).readlines()
    paths = []
    for fname in text:
        if len(fname.strip()) > 0:
            #paths.append(path.join(input_dir, fname.strip()))
            paths.append(fname.strip())
    return paths