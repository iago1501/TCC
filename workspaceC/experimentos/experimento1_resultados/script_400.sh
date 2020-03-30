#!/bin/bash

Rscript --vanilla timexsize_logscale.R experiment1_exectime.txt timexsize_k0.pdf "LPBB k = 0" 3

Rscript --vanilla timexsize_logscale.R experiment1_exectime.txt timexsize_k-1.pdf "LPBB k = -1" 4


