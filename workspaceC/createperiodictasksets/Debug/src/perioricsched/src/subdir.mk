################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/iago/Dropbox/shared_iago/source_codes/workspaceC/perioricsched/src/essentials.c \
/home/iago/Dropbox/shared_iago/source_codes/workspaceC/perioricsched/src/exhaustiveschedule.c \
/home/iago/Dropbox/shared_iago/source_codes/workspaceC/perioricsched/src/scheduler_strict_period_lp.c \
/home/iago/Dropbox/shared_iago/source_codes/workspaceC/perioricsched/src/scheduler_strict_period_lp_bckt.c \
/home/iago/Dropbox/shared_iago/source_codes/workspaceC/perioricsched/src/slibexml.c 

OBJS += \
./src/perioricsched/src/essentials.o \
./src/perioricsched/src/exhaustiveschedule.o \
./src/perioricsched/src/scheduler_strict_period_lp.o \
./src/perioricsched/src/scheduler_strict_period_lp_bckt.o \
./src/perioricsched/src/slibexml.o 

C_DEPS += \
./src/perioricsched/src/essentials.d \
./src/perioricsched/src/exhaustiveschedule.d \
./src/perioricsched/src/scheduler_strict_period_lp.d \
./src/perioricsched/src/scheduler_strict_period_lp_bckt.d \
./src/perioricsched/src/slibexml.d 


# Each subdirectory must supply rules for building sources it contributes
src/perioricsched/src/essentials.o: /home/iago/Dropbox/shared_iago/source_codes/workspaceC/perioricsched/src/essentials.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/home/rguerra/Dropbox/Dropbox/trabalho/pesquisa/Alunos/Iago/shared_iago/source_codes/workspaceC/perioricsched/src -I/usr/lib/i386-linux-gnu/glib-2.0/include -I/home/iago/Dropbox/shared_iago/source_codes/workspaceC/perioricsched/src -I/usr/include/glib-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/perioricsched/src/exhaustiveschedule.o: /home/iago/Dropbox/shared_iago/source_codes/workspaceC/perioricsched/src/exhaustiveschedule.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/home/rguerra/Dropbox/Dropbox/trabalho/pesquisa/Alunos/Iago/shared_iago/source_codes/workspaceC/perioricsched/src -I/usr/lib/i386-linux-gnu/glib-2.0/include -I/home/iago/Dropbox/shared_iago/source_codes/workspaceC/perioricsched/src -I/usr/include/glib-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/perioricsched/src/scheduler_strict_period_lp.o: /home/iago/Dropbox/shared_iago/source_codes/workspaceC/perioricsched/src/scheduler_strict_period_lp.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/home/rguerra/Dropbox/Dropbox/trabalho/pesquisa/Alunos/Iago/shared_iago/source_codes/workspaceC/perioricsched/src -I/usr/lib/i386-linux-gnu/glib-2.0/include -I/home/iago/Dropbox/shared_iago/source_codes/workspaceC/perioricsched/src -I/usr/include/glib-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/perioricsched/src/scheduler_strict_period_lp_bckt.o: /home/iago/Dropbox/shared_iago/source_codes/workspaceC/perioricsched/src/scheduler_strict_period_lp_bckt.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/home/rguerra/Dropbox/Dropbox/trabalho/pesquisa/Alunos/Iago/shared_iago/source_codes/workspaceC/perioricsched/src -I/usr/lib/i386-linux-gnu/glib-2.0/include -I/home/iago/Dropbox/shared_iago/source_codes/workspaceC/perioricsched/src -I/usr/include/glib-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/perioricsched/src/slibexml.o: /home/iago/Dropbox/shared_iago/source_codes/workspaceC/perioricsched/src/slibexml.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/home/rguerra/Dropbox/Dropbox/trabalho/pesquisa/Alunos/Iago/shared_iago/source_codes/workspaceC/perioricsched/src -I/usr/lib/i386-linux-gnu/glib-2.0/include -I/home/iago/Dropbox/shared_iago/source_codes/workspaceC/perioricsched/src -I/usr/include/glib-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


