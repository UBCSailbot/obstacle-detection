def horizon_line(img):
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    edges = cv2.Canny(gray, 160, 256)
    #cv2.imwrite("edge.jpg", edges)
    lines = cv2.HoughLinesP(edges, 1, np.pi/180, 100, None, 30, 12);
    longest_line = 0
    longest_points = ()
    for line in lines[0]:
        pt1 = (line[0],line[1])
        pt2 = (line[2],line[3])
        current_line = ((pt1[0]-pt2[0])**2+(pt1[1]-pt2[1])**2)
        if (current_line > longest_line):
            longest_line = current_line
            longest_points = (pt1, pt2)
    if (longest_line > 0):        
        cv2.line(img, longest_points[0], longest_points[1], (0,0,255), 3)
    return img
