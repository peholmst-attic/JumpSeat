#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-MacOSX
CND_DLIB_EXT=dylib
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/810597573/sqlite3.o \
	${OBJECTDIR}/alert_dispatcher.o \
	${OBJECTDIR}/alert_logger.o \
	${OBJECTDIR}/alert_type_repository.o \
	${OBJECTDIR}/db.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/modem_io.o \
	${OBJECTDIR}/response_dispatcher.o \
	${OBJECTDIR}/sms_logger.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L../boost/stage/lib

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sources

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sources: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sources ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/810597573/sqlite3.o: ../sqlite/sqlite3.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/810597573
	${RM} "$@.d"
	$(COMPILE.c) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/810597573/sqlite3.o ../sqlite/sqlite3.c

${OBJECTDIR}/alert_dispatcher.o: alert_dispatcher.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../boost -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/alert_dispatcher.o alert_dispatcher.cpp

${OBJECTDIR}/alert_logger.o: alert_logger.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../boost -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/alert_logger.o alert_logger.cpp

${OBJECTDIR}/alert_type_repository.o: alert_type_repository.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../boost -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/alert_type_repository.o alert_type_repository.cpp

${OBJECTDIR}/db.o: db.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../boost -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/db.o db.cpp

${OBJECTDIR}/main.o: main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../boost -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/modem_io.o: modem_io.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../boost -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/modem_io.o modem_io.cpp

${OBJECTDIR}/response_dispatcher.o: response_dispatcher.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../boost -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/response_dispatcher.o response_dispatcher.cpp

${OBJECTDIR}/sms_logger.o: sms_logger.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I../boost -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/sms_logger.o sms_logger.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/sources

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
