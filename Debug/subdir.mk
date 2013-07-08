################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../catalysis.cpp \
../commonFunctions.cpp \
../environment.cpp \
../gillespie.cpp \
../main.cpp \
../mtrand.cpp \
../reactions.cpp \
../species.cpp 

OBJS += \
./catalysis.o \
./commonFunctions.o \
./environment.o \
./gillespie.o \
./main.o \
./mtrand.o \
./reactions.o \
./species.o 

CPP_DEPS += \
./catalysis.d \
./commonFunctions.d \
./environment.d \
./gillespie.d \
./main.d \
./mtrand.d \
./reactions.d \
./species.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


