FILE(GLOB SRC_FILES 
	${DIR_SRC}/*.h
	${DIR_SRC}/*.c
)
SOURCE_GROUP("src" FILES ${SRC_FILES})

FILE(GLOB LOCK_FILES 
		${DIR_SRC}/Lock/Mutex.c
		${DIR_SRC}/Lock/Mutex.h
)
SOURCE_GROUP("src/Lock" FILES ${LOCK_FILES})
SET(SRC_FILES ${SRC_FILES} ${LOCK_FILES})