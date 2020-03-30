################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/schedule/sched_data_types.c \
../src/schedule/sched_io.c \
../src/schedule/sched_memory_init.c \
../src/schedule/sched_test.c \
../src/schedule/scheduler_exhaustive_search.c 

OBJS += \
./src/schedule/sched_data_types.o \
./src/schedule/sched_io.o \
./src/schedule/sched_memory_init.o \
./src/schedule/sched_test.o \
./src/schedule/scheduler_exhaustive_search.o 

C_DEPS += \
./src/schedule/sched_data_types.d \
./src/schedule/sched_io.d \
./src/schedule/sched_memory_init.d \
./src/schedule/sched_test.d \
./src/schedule/scheduler_exhaustive_search.d 


# Each subdirectory must supply rules for building sources it contributes
src/schedule/%.o: ../src/schedule/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/home/rguerra/Dropbox/Dropbox/trabalho/pesquisa/Alunos/Iago/shared_iago/source_codes/workspaceC/perioricsched/src -I/usr/lib/i386-linux-gnu/glib-2.0/include -I/home/iago/Dropbox/shared_iago/source_codes/workspaceC/perioricsched/src -I/usr/include/glib-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


