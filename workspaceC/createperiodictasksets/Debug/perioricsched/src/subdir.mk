################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/rguerra/Dropbox/Dropbox/trabalho/pesquisa/Alunos/Iago/shared_iago/source_codes/workspaceC/perioricsched/src/main.c 

OBJS += \
./perioricsched/src/main.o 

C_DEPS += \
./perioricsched/src/main.d 


# Each subdirectory must supply rules for building sources it contributes
perioricsched/src/main.o: /home/rguerra/Dropbox/Dropbox/trabalho/pesquisa/Alunos/Iago/shared_iago/source_codes/workspaceC/perioricsched/src/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/home/rguerra/Dropbox/Dropbox/trabalho/pesquisa/Alunos/Iago/shared_iago/source_codes/workspaceC/perioricsched/src -I/usr/lib/i386-linux-gnu/glib-2.0/include -I/home/iago/Dropbox/shared_iago/source_codes/workspaceC/perioricsched/src -I/usr/include/glib-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


