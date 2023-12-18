# CMPE-283-VirtualTechnologies_Assignment-2and3

Student names: Upasana Kumar, Shireesh Vennamaneni

University Name: San Jose State University

Assignment 2: Instrumentation via hypercall 

Assignment 3: Instrumentation via hypercall (cont’d)


Questions:-

1. For each member in your team, provide 1 paragraph detailing what parts of the lab that member implemented / researched.

Shireesh- He successfully created a VM on Google Cloud Compute Engine using Cloud Shell, where he built the kernel, installed new modules, and reloaded it for updates. He focused on researching and implementing code changes in vmx.c for CPUID leaf nodes 0x4FFFFFFE and 0x4FFFFFFF. After compiling this new code, he updated the VM modules using rmmod and modprobe. He launched the VM on a hypervisor using qemu-system and developed test_assignment.c to validate the modified CPUID hypercalls. Shireesh's testing of the hypercalls with ./test_cpuid.sh, alongside meticulous documentation of the process and results, culminated in his contribution to the GitHub repository, including uploading essential screenshots and enhancing the README.md.

Upasana -She started with enabling SSH authentication on the Google Cloud VM using SSH keys for secure access. She diligently installed the necessary dependencies on the VM, crucial for building the kernel and launching the virtual machine on the hypervisor. Upasana undertook extensive research to implement code changes in cpuid.c for CPUID leaf nodes 0x4FFFFFFE and 0x4FFFFFFF. She upgraded the Ubuntu OS on the VM to the latest version, ensuring system efficiency and security. In her exploration of VM launch methods, Upasana evaluated virt-manager and qemu-system, ultimately opting for qemu-system. After reloading the new modules in the kernel for kvm and kvm_intel, she tested the CPUID functionality and documented the outputs. Her efforts culminated in contributing the dmesg output to the GitHub repository and enhancing the README.md with detailed project insights. 


2. Describe in detail the steps you used to complete the assignment.



3. Comment on the frequency of exits – does the number of exits increase at a stable rate? Or are there more exits performed during certain VM operations? Approximately how many exits does a full VM
   boot entail?

   
4. Of the exit types defined in the SDM, which are the most frequent? Least?


Output Screenshots:-







