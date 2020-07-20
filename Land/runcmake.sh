#!/bin/sh

cmake .. -DCMAKE_BUILD_TYPE=Debug \
		-DON=ON \
		-DBUILDS_DIRS=${BUILDS_DIR} \
		-DHOME_DIR=${HOME_DIR} \
		-G"Eclipse CDT4 - Unix Makefiles" \
		-DENABLE_DOXYGEN=O


