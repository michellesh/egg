import bpy
import math
from numpy import linspace


def poc(radius, origin, d):
    '''returns a point `d` degrees along the circumference of a circle with given `radius` and `origin` point'''
    degrees = d + 270 if d - 90 < 0 else d - 90
    radians = (degrees * math.pi) / 180
    x = origin[0] + radius * math.cos(radians)
    y = origin[1] + radius * math.sin(radians)
    return (x, y, origin[2])


def create_mesh_obj(verts, edges, faces):
    mesh_data = bpy.data.meshes.new("led_data")
    mesh_data.from_pydata(verts, edges, faces)
    mesh_obj = bpy.data.objects.new("led_object", mesh_data)
    bpy.context.collection.objects.link(mesh_obj)
    return mesh_obj


def move(v, x=0, y=0, z=0):
    return (v[0] + x, v[1] + y, v[2] + z)


top_vert = (0, 0, 122.5)
thickness = 5    # how thick each ring is in millimeters

# number of vertices in each circle
circle_num_vertices = [6, 12, 16, 22, 24, 28, 30, 30, 30, 28, 24, 22, 16]

# z coordinate of each circle
circle_z = [
    119.86, 112.36, 100.8, 86.03, 68.97, 50.54, 31.6, 12.91, -4.85, -21.11,
    -35.46, -47.55, -57.15
]

# diameter of each circle
circle_diameter = [
    27.31, 53.58, 77.78, 98.99, 116.41, 129.34, 137.31, 140, 137.31, 129.34,
    116.41, 98.99, 77.78
]

# horizontal rings
verts = [top_vert]
edges = []
faces = []
start_index = 1

# vertical rings
v_verts = [move(top_vert, x=thickness / 2), move(top_vert, x=thickness / -2)]
v_verts.extend([move(v_verts[0], z=-thickness), move(v_verts[1], z=-thickness)])
v_edges = []
v_faces = []

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

    # vertical rings vertices: outer ring
    z = 0 if i < 7 else thickness / -2 if i == 7 else -thickness
    v_verts.extend([
        move(poc(radius, origin, 0), x=thickness / 2, z=z),
        move(poc(radius, origin, 0), x=thickness / -2, z=z),
        move(poc(radius, origin, 180), x=thickness / 2, z=z),
        move(poc(radius, origin, 180), x=thickness / -2, z=z),
    ])

    # vertical rings vertices: inner ring
    z = -thickness if i < 7 else 0 if i == 7 else thickness
    v_verts.extend([
        move(v_verts[len(v_verts) - 4], y=thickness, z=z),
        move(v_verts[len(v_verts) - 3], y=thickness, z=z),
        move(v_verts[len(v_verts) - 2], y=-thickness, z=z),
        move(v_verts[len(v_verts) - 1], y=-thickness, z=z),
    ])

    # vertical rings faces
    if i == 0:
        v_faces.extend([
            (0, 4, 5, 1),
            (1, 5, 9, 3),
            (3, 9, 8, 2),
            (2, 8, 4, 0),
            (0, 6, 7, 1),
            (1, 7, 11, 3),
            (3, 11, 10, 2),
            (2, 10, 6, 0),
        ])
    else:
        n = len(v_verts)
        v_faces.extend([
            (n - 1, n - 9, n - 10, n - 2),
            (n - 2, n - 10, n - 14, n - 6),
            (n - 6, n - 14, n - 13, n - 5),
            (n - 5, n - 13, n - 9, n - 1),
            (n - 3, n - 11, n - 12, n - 4),
            (n - 4, n - 12, n - 16, n - 8),
            (n - 8, n - 16, n - 15, n - 7),
            (n - 7, n - 15, n - 11, n - 3),
        ])

    # add vertices for this circle
    verts.extend([poc(radius, origin, d) for d in circle_degrees])    # circle1
    verts.extend([poc(radius - thickness, origin, d)
                  for d in circle_degrees])    # circle2
    origin = (0, 0, circle_z[i] - thickness)
    verts.extend([poc(radius, origin, d) for d in circle_degrees])    # circle3
    verts.extend([poc(radius - thickness, origin, d)
                  for d in circle_degrees])    # circle4

    n = len(verts) - 1
    nc = circle_num_vertices[i]

    for i in range(start_index, start_index + nc):
        v1 = start_index if i == start_index + nc - 1 else i + 1
        v2 = start_index + nc if i == start_index + nc - 1 else nc + i + 1
        v3 = start_index + nc * 2 if i == start_index + nc - 1 else nc * 2 + i + 1
        v4 = start_index + nc * 3 if i == start_index + nc - 1 else nc * 3 + i + 1

        # connect circle1 to circle2
        faces.extend([(i, v1, v2, nc + i)])
        # connect circle1 to circle3
        faces.extend([(i, v1, v3, nc * 2 + i)])
        # connect circle2 to circle4
        faces.extend([(nc + i, v2, v4, nc * 3 + i)])
        # connect circle3 to circle4
        faces.extend([(nc * 2 + i, v3, v4, nc * 3 + i)])

    start_index = len(verts)

# vertical rings, add faces to connect the bottom two joints
n = len(v_verts)
v_faces.extend([
    (n - 1, n - 3, n - 4, n - 2),
    (n - 2, n - 4, n - 8, n - 6),
    (n - 6, n - 8, n - 7, n - 5),
    (n - 5, n - 7, n - 3, n - 1),
])

create_mesh_obj(verts, edges, faces)
create_mesh_obj(v_verts, v_edges, v_faces)
obj = create_mesh_obj(v_verts, v_edges, v_faces)
obj.rotation_euler = (0, 0, math.radians(90))
