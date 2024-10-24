#!/bin/bash

sed -e '/solid/d' -e '/outer/d' -e '/end/d' -e 's/facet\snormal\s//g' -e 's/vertex\s//g' -e 's/\s/\n/g' $1 > STLoutput.txt
#
