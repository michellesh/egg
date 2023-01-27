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


top_vert = (0, 0, 122.5)

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

# distance between LEDs in each circle (just for debugging)
dists = []

verts = [top_vert]
faces = []
edges = []

for i in range(len(circle_num_vertices)):

    # list of degree increments for each point on this circle
    circle_degrees = linspace(0, 360, circle_num_vertices[i], endpoint=False)
    radius = circle_diameter[i] / 2
    origin = (0, 0, circle_z[i])

    # add vertices for this circle
    circle_verts = [poc(radius, origin, d) for d in circle_degrees]
    verts.extend(circle_verts)
    dists.append(math.dist(circle_verts[0], circle_verts[1]))

    # add edges for this circle
    edges.append((len(verts) - len(circle_verts), len(verts) - 1))
    for i in range(len(verts) - 1, len(verts) - len(circle_verts), -1):
        edges.append((i, i - 1))

# create mesh and add to blender
mesh_data = bpy.data.meshes.new("led_data")
mesh_data.from_pydata(verts, edges, faces)

mesh_obj = bpy.data.objects.new("led_object", mesh_data)

bpy.context.collection.objects.link(mesh_obj)
