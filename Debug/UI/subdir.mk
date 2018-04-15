################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../UI/Button.cpp \
../UI/LoadMenu.cpp \
../UI/LoanMenu.cpp \
../UI/MainMenu.cpp \
../UI/NewMenu.cpp \
../UI/SaveMenu.cpp \
../UI/StartMenu.cpp \
../UI/TaxMenu.cpp \
../UI/TextBox.cpp \
../UI/TextField.cpp 

OBJS += \
./UI/Button.o \
./UI/LoadMenu.o \
./UI/LoanMenu.o \
./UI/MainMenu.o \
./UI/NewMenu.o \
./UI/SaveMenu.o \
./UI/StartMenu.o \
./UI/TaxMenu.o \
./UI/TextBox.o \
./UI/TextField.o 

CPP_DEPS += \
./UI/Button.d \
./UI/LoadMenu.d \
./UI/LoanMenu.d \
./UI/MainMenu.d \
./UI/NewMenu.d \
./UI/SaveMenu.d \
./UI/StartMenu.d \
./UI/TaxMenu.d \
./UI/TextBox.d \
./UI/TextField.d 


# Each subdirectory must supply rules for building sources it contributes
UI/%.o: ../UI/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=gnu++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


