################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/rguerra/Dropbox/Dropbox/trabalho/pesquisa/Alunos/Iago/shared_iago/source_codes/workspaceC/perioricsched/src/schedule/sched_data_types.c \
/home/rguerra/Dropbox/Dropbox/trabalho/pesquisa/Alunos/Iago/shared_iago/source_codes/workspaceC/perioricsched/src/schedule/sched_io.c \
/home/rguerra/Dropbox/Dropbox/trabalho/pesquisa/Alunos/Iago/shared_iago/source_codes/workspaceC/perioricsched/src/schedule/sched_memory_init.c \
/home/rguerra/Dropbox/Dropbox/trabalho/pesquisa/Alunos/Iago/shared_iago/source_codes/workspaceC/perioricsched/src/schedule/sched_test.c \
/home/rguerra/Dropbox/Dropbox/trabalho/pesquisa/Alunos/Iago/shared_iago/source_codes/workspaceC/perioricsched/src/schedule/scheduler_exhaustive_search.c \
/home/rguerra/Dropbox/Dropbox/trabalho/pesquisa/Alunos/Iago/shared_iago/source_codes/workspaceC/perioricsched/src/schedule/scheduler_strict_period_lp.c \
/home/rguerra/Dropbox/Dropbox/trabalho/pesquisa/Alunos/Iago/shared_iago/source_codes/workspaceC/perioricsched/src/schedule/scheduler_strict_period_lp_bckt.c \
/home/rguerra/Dropbox/Dropbox/trabalho/pesquisa/Alunos/Iago/shared_iago/source_codes/workspaceC/perioricsched/src/schedule/scheduler_strict_period_lp_bckt_hrsts.c 

OBJS += \
./perioricsched/src/schedule/sched_data_types.o \
./perioricsched/src/schedule/sched_io.o \
./perioricsched/src/schedule/sched_memory_init.o \
./perioricsched/src/schedule/sched_test.o \
./perioricsched/src/schedule/scheduler_exhaustive_search.o \
./perioricsched/src/schedule/scheduler_strict_period_lp.o \
./perioricsched/src/schedule/scheduler_strict_period_lp_bckt.o \
./perioricsched/src/schedule/scheduler_strict_period_lp_bckt_hrsts.o 

C_DEPS += \
./perioricsched/src/schedule/sched_data_types.d \
./perioricsched/src/schedule/sched_io.d \
./perioricsched/src/schedule/sched_memory_init.d \
./perioricsched/src/schedule/sched_test.d \
./perioricsched/src/schedule/scheduler_exhaustive_search.d \
./perioricsched/src/schedule/scheduler_strict_period_lp.d \
./perioricsched/src/schedule/scheduler_strict_period_lp_bckt.d \
./perioricsched/src/schedule/scheduler_strict_period_lp_bckt_hrsts.d 


# Each subdirectory must supply rules for building sources it contributes
perioricsched/src/schedule/sched_data_types.o: /home/rguerra/Dropbox/Dropbox/trabalho/pesquisa/Alunos/Iago/shared_iago/source_codes/workspaceC/perioricsched/src/schedule/sched_data_types.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/home/rguerra/Dropbox/Dropbox/trabalho/pesquisa/Alunos/Iago/shared_iago/source_codes/workspaceC/perioricsched/src -I/usr/lib/i386-linux-gnu/glib-2.0/include -I/home/iago/Dropbox/shared_iago/source_codes/workspaceC/perioricsched/src -I/usr/include/glib-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

perioricsched/src/schedule/sched_io.o: /home/rguerra/Dropbox/Dropbox/trabalho/pesquisa/Alunos/Iago/shared_iago/source_codes/workspaceC/perioricsched/src/schedule/sched_io.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/home/rguerra/Dropbox/Dropbox/trabalho/pesquisa/Alunos/Iago/shared_iago/source_codes/workspaceC/perioricsched/src -I/usr/lib/i386-linux-gnu/glib-2.0/include -I/home/iago/Dropbox/shared_iago/source_codes/workspaceC/perioricsched/src -I/usr/include/glib-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

perioricsched/src/schedule/sched_memory_init.o: /home/rguerra/Dropbox/Dropbox/trabalho/pesquisa/Alunos/Iago/shared_iago/source_codes/workspaceC/perioricsched/src/schedule/sched_memory_init.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/home/rguerra/Dropbox/Dropbox/trabalho/pesquisa/Alunos/Iago/shared_iago/source_codes/workspaceC/perioricsched/src -I/usr/lib/i386-linux-gnu/glib-2.0/include -I/home/iago/Dropbox/shared_iago/source_codes/workspaceC/perioricsched/src -I/usr/include/glib-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

perioricsched/src/schedule/sched_test.o: /home/rguerra/Dropbox/Dropbox/trabalho/pesquisa/Alunos/Iago/shared_iago/source_codes/workspaceC/perioricsched/src/schedule/sched_test.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/home/rguerra/Dropbox/Dropbox/trabalho/pesquisa/Alunos/Iago/shared_iago/source_codes/workspaceC/perioricsched/src -I/usr/lib/i386-linux-gnu/glib-2.0/include -I/home/iago/Dropbox/shared_iago/source_codes/workspaceC/perioricsched/src -I/usr/include/glib-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

perioricsched/src/schedule/scheduler_exhaustive_search.o: /home/rguerra/Dropbox/Dropbox/trabalho/pesquisa/Alunos/Iago/shared_iago/source_codes/workspaceC/perioricsched/src/schedule/scheduler_exhaustive_search.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/home/rguerra/Dropbox/Dropbox/trabalho/pesquisa/Alunos/Iago/shared_iago/source_codes/workspaceC/perioricsched/src -I/usr/lib/i386-linux-gnu/glib-2.0/include -I/home/iago/Dropbox/shared_iago/source_codes/workspaceC/perioricsched/src -I/usr/include/glib-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

perioricsched/src/schedule/scheduler_strict_period_lp.o: /home/rguerra/Dropbox/Dropbox/trabalho/pesquisa/Alunos/Iago/shared_iago/source_codes/workspaceC/perioricsched/src/schedule/scheduler_strict_period_lp.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/home/rguerra/Dropbox/Dropbox/trabalho/pesquisa/Alunos/Iago/shared_iago/source_codes/workspaceC/perioricsched/src -I/usr/lib/i386-linux-gnu/glib-2.0/include -I/home/iago/Dropbox/shared_iago/source_codes/workspaceC/perioricsched/src -I/usr/include/glib-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

perioricsched/src/schedule/scheduler_strict_period_lp_bckt.o: /home/rguerra/Dropbox/Dropbox/trabalho/pesquisa/Alunos/Iago/shared_iago/source_codes/workspaceC/perioricsched/src/schedule/scheduler_strict_period_lp_bckt.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/home/rguerra/Dropbox/Dropbox/trabalho/pesquisa/Alunos/Iago/shared_iago/source_codes/workspaceC/perioricsched/src -I/usr/lib/i386-linux-gnu/glib-2.0/include -I/home/iago/Dropbox/shared_iago/source_codes/workspaceC/perioricsched/src -I/usr/include/glib-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

perioricsched/src/schedule/scheduler_strict_period_lp_bckt_hrsts.o: /home/rguerra/Dropbox/Dropbox/trabalho/pesquisa/Alunos/Iago/shared_iago/source_codes/workspaceC/perioricsched/src/schedule/scheduler_strict_period_lp_bckt_hrsts.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/home/rguerra/Dropbox/Dropbox/trabalho/pesquisa/Alunos/Iago/shared_iago/source_codes/workspaceC/perioricsched/src -I/usr/lib/i386-linux-gnu/glib-2.0/include -I/home/iago/Dropbox/shared_iago/source_codes/workspaceC/perioricsched/src -I/usr/include/glib-2.0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


