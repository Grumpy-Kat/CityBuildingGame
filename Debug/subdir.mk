################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../AnimatedSprite.cpp \
../Building.cpp \
../BuildingType.cpp \
../Camera.cpp \
../FireManager.cpp \
../Main.cpp \
../MapGenerator.cpp \
../MenuManager.cpp \
../MoneyManager.cpp \
../MouseManager.cpp \
../PopulationManager.cpp \
../Sprite.cpp \
../SpriteManager.cpp \
../Tile.cpp \
../UIManager.cpp \
../Window.cpp \
../WindowManager.cpp \
../World.cpp \
../WorldManager.cpp 

OBJS += \
./AnimatedSprite.o \
./Building.o \
./BuildingType.o \
./Camera.o \
./FireManager.o \
./Main.o \
./MapGenerator.o \
./MenuManager.o \
./MoneyManager.o \
./MouseManager.o \
./PopulationManager.o \
./Sprite.o \
./SpriteManager.o \
./Tile.o \
./UIManager.o \
./Window.o \
./WindowManager.o \
./World.o \
./WorldManager.o 

CPP_DEPS += \
./AnimatedSprite.d \
./Building.d \
./BuildingType.d \
./Camera.d \
./FireManager.d \
./Main.d \
./MapGenerator.d \
./MenuManager.d \
./MoneyManager.d \
./MouseManager.d \
./PopulationManager.d \
./Sprite.d \
./SpriteManager.d \
./Tile.d \
./UIManager.d \
./Window.d \
./WindowManager.d \
./World.d \
./WorldManager.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=gnu++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


