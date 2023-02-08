import bpy
import math
from numpy import linspace


def poc(radius, origin, d):
    '''get a point on the circumference of a circle
    d : degrees along the circumference of the cricle
    radius : radius of the circle
    origin : (x, y, z) center coordinates of the circle
    '''
    degrees = d + 270 if d - 90 < 0 else d - 90
    radians = (degrees * math.pi) / 180
    x = origin[0] + radius * math.cos(radians)
    y = origin[1] + radius * math.sin(radians)
    return (x, y, origin[2])


def pol(p1, p2, how_far):
    '''get a point on the line that forms between p1 and p2
    p1 : (x, y, z) start point of line
    p2 : (x, y, z) end point of line
    how_far : value between 0 and 1, how far along the line
    '''
    return (p1[0] + (p2[0] - p1[0]) * how_far,
            p1[1] + (p2[1] - p1[1]) * how_far,
            p1[2] + (p2[2] - p1[2]) * how_far)


def distance(p1, p2):
    return math.sqrt((p2[0] - p1[0])**2 + (p2[1] - p1[1])**2 +
                     (p2[2] - p1[2])**2)


def create_mesh_obj(verts, edges, faces, name="mesh"):
    mesh_data = bpy.data.meshes.new(name + "_data")
    mesh_data.from_pydata(verts, edges, faces)
    mesh_obj = bpy.data.objects.new(name, mesh_data)
    bpy.context.collection.objects.link(mesh_obj)
    return mesh_obj


def move(v, x=0, y=0, z=0):
    return (v[0] + x, v[1] + y, v[2] + z)


top_vert = (0, 0, 124)
thickness = 4    # how thick each ring is in millimeters

# number of vertices in each circle
circle_num_vertices = [
    # Distance between LEDs in each ring:
    7,    # Ring 0: [5, 6, 7] [19.42, 16.52, 14.34]
    11,    # Ring 1: [10, 11, 12] [18.94, 17.27, 15.86]
    15,    # Ring 2: [14, 15, 16] [18.77, 17.54, 16.46]
    19,    # Ring 3: [18, 19, 20] [17.88, 16.95, 16.11]
    21,    # Ring 4: [20, 21, 22] [18.42, 17.55, 16.76]
    23,    # Ring 5: [22, 23, 24] [18.35, 17.55, 16.83]
    25,    # Ring 6: [24, 25, 26] [17.78, 17.07, 16.42]
    25,    # Ring 7: [24, 25, 26] [18.23, 17.5, 16.83]
    25,    # Ring 8: [24, 25, 26] [18.1, 17.38, 16.71]
    25,    # Ring 9: [23, 24, 25] [18.05, 17.31, 16.62]
    23,    # Ring 10: [21, 22, 23] [17.98, 17.17, 16.43]
    19,    # Ring 11: [17, 18, 19] [18.8, 17.76, 16.84]
    15,    # Ring 12: [13, 14, 15] [18.61, 17.31, 16.17]
]

# z coordinate of each circle
circle_z = [
    119.978, 110.52, 98.0201, 83.8016, 68.496, 52.4351, 35.8279, 18.9098,
    1.91173, -14.8137, -30.7232, -45.036, -56.8221
]

# diameter of each circle
circle_diameter = [
    33.0401, 61.2911, 84.3618, 102.988, 117.7806, 128.9127, 136.2106, 139.6347,
    138.668, 132.5939, 120.6395, 102.3022, 77.7783
]

# horizontal rings
verts = [top_vert]
edges = []
faces = []
start_index = 1
prev_start_vertex = verts[0]

# horizontal rings for notches
notch_verts = [top_vert]

# vertical rings
v_verts = [
    move(top_vert, x=thickness / 2),
    move(top_vert, x=thickness / -2),
    move(top_vert, x=thickness / 2, z=-thickness),
    move(top_vert, x=thickness / -2, z=-thickness)
]
v_edges = []
v_faces = [
    (0, 4, 5, 1),
    (1, 5, 9, 3),
    (3, 9, 8, 2),
    (2, 8, 4, 0),
    (0, 6, 7, 1),
    (1, 7, 11, 3),
    (3, 11, 10, 2),
    (2, 10, 6, 0),
]

# vertical ring inner notches for taking the diff out of horizontal rings
v_notch_verts = [
    move(top_vert, x=thickness / 2),
    move(top_vert, x=thickness / -2),
    move(top_vert, x=thickness / 2, z=thickness / -2),
    move(top_vert, x=thickness / -2, z=thickness / -2),
]

# vertical ring inner notches for taking the diff out of the other vertical ring
v_notch_inner_verts = [
    move(top_vert, x=thickness / 2, z=thickness / -2),
    move(top_vert, x=thickness / -2, z=thickness / -2),
    move(top_vert, x=thickness / 2, z=-thickness),
    move(top_vert, x=thickness / -2, z=-thickness),
]

#  (above)           |  (below)
#  outer=1, inner=2  |  outer=3, inner=4
#--------------------+----------------------
#         1          |           13
#         7          |           19
#  0 6         8 2   |   12 18         20 14
#                    |
#                    |
#  5 11        9 3   |   17 11         21 15
#         10         |           22
#         4          |           16

for i in range(len(circle_num_vertices)):

    # list of degree increments for each point on this circle
    circle_degrees = linspace(0, 360, circle_num_vertices[i], endpoint=False)
    radius = circle_diameter[i] / 2
    origin = (0, 0, circle_z[i])

    # calculate the first vertex (at 0 degrees) for each circle
    c1 = poc(radius, origin, 0)
    how_far = thickness / distance(c1, prev_start_vertex)
    c2 = pol(c1, prev_start_vertex, how_far)
    c3 = (c1[0], c1[1] + (c2[2] - c1[2]), c1[2] - (c2[1] - c1[1]))
    c4 = (c3[0], c3[1] + (c1[2] - c3[2]), c3[2] - (c1[1] - c3[1]))
    notch_c1 = pol(c1, c3, 0.5)
    notch_c2 = pol(c2, c4, 0.5)

    # horizontal rings vertices at each degree increment around each circle
    origin = (0, 0, c1[2])
    radius = distance(c1, origin)
    c1_180 = poc(radius, origin, 180)
    verts.extend([poc(radius, origin, d) for d in circle_degrees])    # circle1

    origin = (0, 0, c2[2])
    radius = distance(c2, origin)
    verts.extend([poc(radius, origin, d) for d in circle_degrees])    # circle2

    origin = (0, 0, c3[2])
    radius = distance(c3, origin)
    c3_180 = poc(radius, origin, 180)
    verts.extend([poc(radius, origin, d) for d in circle_degrees])    # circle3

    origin = (0, 0, c4[2])
    radius = distance(c4, origin)
    verts.extend([poc(radius, origin, d) for d in circle_degrees])    # circle4

    # horizontal notch rings vertices
    origin = (0, 0, notch_c1[2])
    radius = distance(notch_c1, origin)
    notch_verts.extend([poc(radius, origin, d)
                        for d in circle_degrees])    # circle1

    origin = (0, 0, notch_c2[2])
    radius = distance(notch_c2, origin)
    notch_verts.extend([poc(radius, origin, d)
                        for d in circle_degrees])    # circle2

    origin = (0, 0, c3[2])
    radius = distance(c3, origin)
    notch_verts.extend([poc(radius, origin, d)
                        for d in circle_degrees])    # circle3

    origin = (0, 0, c4[2])
    radius = distance(c4, origin)
    notch_verts.extend([poc(radius, origin, d)
                        for d in circle_degrees])    # circle4

    # horizontal rings faces
    nc = circle_num_vertices[i]
    for i in range(start_index, start_index + nc):
        v1 = start_index if i == start_index + nc - 1 else i + 1
        v2 = start_index + nc if i == start_index + nc - 1 else nc + i + 1
        v3 = start_index + nc * 2 if i == start_index + nc - 1 else nc * 2 + i + 1
        v4 = start_index + nc * 3 if i == start_index + nc - 1 else nc * 3 + i + 1

        faces.extend([
            (i, v1, v2, nc + i),    # connect circle1 to circle2
            (i, v1, v3, nc * 2 + i),    # connect circle1 to circle3
            (nc + i, v2, v4, nc * 3 + i),    # connect circle2 to circle4
            (nc * 2 + i, v3, v4, nc * 3 + i),    # connect circle3 to circle4
        ])

    # vertical rings vertices
    v_verts.extend([
        move(c1, x=thickness / 2),
        move(c1, x=thickness / -2),
        move(c1_180, x=thickness / 2),
        move(c1_180, x=thickness / -2),
        move(c3, x=thickness / 2),
        move(c3, x=thickness / -2),
        move(c3_180, x=thickness / 2),
        move(c3_180, x=thickness / -2),
    ])

    # vertical notch rings vertices
    c1_c3 = pol(c1, c3, 0.5)
    c1_c3_180 = pol(c1_180, c3_180, 0.5)
    v_notch_verts.extend([
        move(c1, x=thickness / 2),
        move(c1, x=thickness / -2),
        move(c1_180, x=thickness / 2),
        move(c1_180, x=thickness / -2),
        move(c1_c3, x=thickness / 2),
        move(c1_c3, x=thickness / -2),
        move(c1_c3_180, x=thickness / 2),
        move(c1_c3_180, x=thickness / -2),
    ])

    v_notch_inner_verts.extend([
        move(c1_c3, x=thickness / 2),
        move(c1_c3, x=thickness / -2),
        move(c1_c3_180, x=thickness / 2),
        move(c1_c3_180, x=thickness / -2),
        move(c3, x=thickness / 2),
        move(c3, x=thickness / -2),
        move(c3_180, x=thickness / 2),
        move(c3_180, x=thickness / -2),
    ])

    prev_start_vertex = verts[start_index]
    start_index = len(verts)

# vertical rings faces
for i in range(len(circle_num_vertices) - 1):
    v = i * 8 + 4
    v_faces.extend([
        (v + 0, v + 8, v + 9, v + 1),
        (v + 1, v + 9, v + 13, v + 5),
        (v + 5, v + 13, v + 12, v + 4),
        (v + 4, v + 12, v + 8, v + 0),
        (v + 2, v + 10, v + 11, v + 3),
        (v + 3, v + 11, v + 15, v + 7),
        (v + 7, v + 15, v + 14, v + 6),
        (v + 6, v + 14, v + 10, v + 2),
    ])

# vertical rings, add faces to connect the bottom two joints
n = len(v_verts)
v_faces.extend([
    (n - 1, n - 3, n - 4, n - 2),
    (n - 2, n - 4, n - 8, n - 6),
    (n - 6, n - 8, n - 7, n - 5),
    (n - 5, n - 7, n - 3, n - 1),
])

create_mesh_obj(verts, edges, faces, name="horizontal_rings")
create_mesh_obj(notch_verts, edges, faces, name="horizontal_notches")

create_mesh_obj(v_verts, v_edges, v_faces, name="vertical_ring_1")
obj = create_mesh_obj(v_verts, v_edges, v_faces, name="vertical_ring_2")
obj.rotation_euler = (0, 0, math.radians(90))

create_mesh_obj(v_notch_verts, v_edges, v_faces, name="vertical_notches_1")
obj = create_mesh_obj(v_notch_verts,
                      v_edges,
                      v_faces,
                      name="vertical_notches_2")
obj.rotation_euler = (0, 0, math.radians(90))

create_mesh_obj(v_notch_inner_verts,
                v_edges,
                v_faces,
                name="vertical_notches_inner")
