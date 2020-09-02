#!/bin/sh

glslc frag_inter.frag -o frag_inter.spv
glslc frag_sampler.frag -o frag_sampler.spv
glslc vert_linestrip.vert -o vert_linestrip.spv
glslc vert_uniform.vert -o vert_uniform.spv
