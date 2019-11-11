def ROI_definition():
    ROI_list = []
    # ROI for ETS_H_list
    pt1 = (580,390)
    pt2 = (750,390)
    pt3 = (1280,720)
    pt4 = (80,720)
    ROI_list.append(np.array([[pt1, pt2, pt3, pt4]], dtype=np.int32))
    # ROI for PC_F_list
    pt1 = (330,300)
    pt2 = (500,300)
    pt3 = (1100,450)
    pt4 = (-300,450)
    ROI_list.append(np.array([[pt1, pt2, pt3, pt4]],\
     dtype=np.int32))
    # ROI for PC_H_list
    pt1 = (200,300)
    pt2 = (620,300)
    pt3 = (1100,450)
    pt4 = (-300,450)
    ROI_list.append(np.array([[pt1, pt2, pt3, pt4]],\
     dtype=np.int32))
    # ROI for PC_T_list
    pt1 = (250,300)
    pt2 = (550,300)
    pt3 = (800,430)
    pt4 = (0,430)
    ROI_list.append(np.array([[pt1, pt2, pt3, pt4]],\
     dtype=np.int32))
    return ROI_list