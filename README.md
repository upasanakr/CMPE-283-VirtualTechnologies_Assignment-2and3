# CMPE-283-VirtualTechnologies_Assignment-2 and 3

## Assignment 2 and 3 - Instrumentation via hypercall
Student names: <a href="https://www.linkedin.com/in/upasana-kumar/"> Upasana Kumar</a>, <a href="https://www.linkedin.com/in/shireesh-vennamaneni-9b906914a/">Shireesh Vennamaneni</a>  

University Name: San Jose State University  

Prerequisites:- You require a machine that supports Linux and has VMX virtualization features available. Need working setup from <a href="https://github.com/upasanakr/CMPE-283-VirtualTechnologies_Assignment-1">Assignment 1</a>  

Assignment Details:- CPUID emulation code in KVM is modified to report back additional information when special CPUID leaf nodes are requested.  

Pushed the code to the forked linux repository also: https://github.com/shireesh20/linux 

## Steps to run the code

#### Step-1
Clone this repository  
#### Step-2
Copy vmx.c file to linux in your vm  
```cp vmx.c ~/linux/arch/x86/kvm/vmx/```  
#### Step-3
Copy cpuid.c file to linux in your vm  
```cp cpuid.c ~/linux/arch/x86/kvm/```
#### Step-4
Follow the steps mentioned in the answer to Question 2 in the Questions section below. 

## Questions:-  

### 1. For each member in your team, provide 1 paragraph detailing what parts of the lab that member implemented / researched.

Shireesh- He successfully created a VM on Google Cloud Compute Engine using Cloud Shell, where he built the kernel, installed new modules, and reloaded it for updates. He focused on researching and implementing code changes in vmx.c for CPUID leaf nodes 0x4FFFFFFE and 0x4FFFFFFF. After compiling this new code, he updated the VM modules using rmmod and modprobe. He launched the VM on a hypervisor using qemu-system and developed test.c to validate the modified CPUID hypercalls. Shireesh's testing of the hypercalls with, alongside meticulous documentation of the process and results, culminated in his contribution to the GitHub repository, including uploading essential screenshots and enhancing the README.md.

Upasana -She started with enabling SSH authentication on the Google Cloud VM using SSH keys for secure access. She diligently installed the necessary dependencies on the VM, crucial for building the kernel and launching the virtual machine on the hypervisor. Upasana undertook extensive research to implement code changes in cpuid.c for CPUID leaf nodes 0x4FFFFFFE and 0x4FFFFFFF. She upgraded the Ubuntu OS on the VM to the latest version, ensuring system efficiency and security. In her exploration of VM launch methods, Upasana evaluated virt-manager and qemu-system, ultimately opting for qemu-system. After reloading the new modules in the kernel for kvm and kvm_intel, she tested the CPUID functionality and documented the outputs. Her efforts culminated in contributing the dmesg output to the GitHub repository and enhancing the README.md with detailed project insights. 


### 2. Describe in detail the steps you used to complete the assignment.  
#### Step-1  
```cd linux/arch/x86/kvm```  
#### Step-2  
```vi cpuid.c```, changed the code in cpuid.c's kvm_emulate_cpuid function to handle the special %eax values that are being implemented in this assignment.
#### Step-3  
```cd vmx```
#### Step-4  
```vi vmx.c```, change the code of how the exits are handled in vmx_handle_exit and __vmx_handle_exit functions to include the functionality of counting the number of exits, time taken for the exit in cpu cycles
#### Step-5  
Run ```sudo make -j 8 module```  
<img width="1472" alt="Screenshot 2023-12-17 at 10 18 09 PM" src="https://github.com/upasanakr/CMPE-283-VirtualTechnologies_Assignment-2and3/assets/37268397/d67105dc-8832-4596-ab82-6cc2baae5208">  

If there is any error at init.c, run the below commands:

```
sudo mount -t tmpfs - /usr/local/
scripts/config --disable SYSTEM_TRUSTED_KEYS
scripts/config --disable SYSTEM_REVOCATION_KEYS
scripts/config --enable SYSTEM_REVOCATION_KEYS
scripts/config --enable SYSTEM_TRUSTED_KEYS
```
#### Step-6
If the module build is successful, run the command to install the modules

```sudo make INSTALL_MOD_STRIP=1 modules_install```

#### Step-7 
Delete and load the kvm_intel and kvm modules using

```
sudo rmmod kvm_intel
sudo rmmod kvm
sudo modprobe kvm_intel
sudo modprobe kvm
```

#### Step-8
Now that the modules are built, we need an inner vm to test this code. Follow the below steps to launch an inner vm

```wget https://cloud-images.ubuntu.com/bionic/current/bionic-server-cloudimg-amd64.img```  

<img width="1690" alt="wget" src="https://github.com/upasanakr/CMPE-283-VirtualTechnologies_Assignment-2and3/assets/37268397/6e078dd9-c568-4fc5-8ac7-1c3f30a881dc">

Create user-data file and copy the content:
```
#cloud-config
password: <password>
chpasswd: { expire: False }
ssh_pwauth: True
```

Run ```cloud-localds user-data.img user-data```  
Run ```sudo apt-get install qemu-kvm qemu virt-manager virt-viewer libvirt-daemon```  
<img width="1701" alt="qemu" src="https://github.com/upasanakr/CMPE-283-VirtualTechnologies_Assignment-2and3/assets/37268397/9b22c8b8-a1e3-4918-8c30-e18f2f11f771">

Run ```sudo qemu-system-x86_64 -enable-kvm -hda bionic-server-cloudimg-amd64.img -drive "file=user-data.img,format=raw" -m 512 -curses -nographic``` to launch the vm. Give ubuntu as username and <password> to login.  
<img width="696" alt="inner-vm" src="https://github.com/upasanakr/CMPE-283-VirtualTechnologies_Assignment-2and3/assets/37268397/9f2193d4-e765-4244-8b38-4bd6b98bc2ef">

#### Step-9
Now in the inner vm, install cpuid using ```sudo apt-get update``` and ```sudo apt install cpuid```
#### Step-10
You can verify by calling cpuid with eax value: ```cpuid -l 0x4FFFFFFF``` and so on.
#### Step-11
You can also write a C or Python program to run these tests. Sample file is attached in this repository.
#### Step-12
```gcc test.c```
<img width="1245" alt="Screenshot 2023-12-17 at 6 48 44 PM" src="https://github.com/upasanakr/CMPE-283-VirtualTechnologies_Assignment-2and3/assets/37268397/3a1f4d4f-47d6-42ab-b774-e34a868599de">
#### Step-13
```./a.out``` or ```./a.out <ecx_value>```

<img width="831" alt="Screenshot 2023-12-17 at 6 52 33 PM" src="https://github.com/upasanakr/CMPE-283-VirtualTechnologies_Assignment-2and3/assets/37268397/c6f5c222-04b3-4b61-96eb-353ed71dfa25">


### 3. Comment on the frequency of exits – does the number of exits increase at a stable rate? Or are there more exits performed during certain VM operations? Approximately how many exits does a full VM boot entail?

* Ran the test C file for 5 times in 5 sec i.e, running once every sec and the following output is seen  
<img width="854" alt="Screenshot 2023-12-17 at 9 13 15 PM" src="https://github.com/upasanakr/CMPE-283-VirtualTechnologies_Assignment-2and3/assets/37268397/6ba0fbf3-035b-4f5e-88c2-163a6dc246e0">

The first call reported 6240492 exits.  
The second call reported 6241334 exits, an increase of 842.  
The third call reported 6242201 exits, an increase of 867.  
The fourth call reported 6243003 exits, an increase of 802.  
The fifth call reported 6243790 exits, an increase of 787.  
This indicates that the number of exits is increasing at an almost steady rate.  

* To test the number of exits that occur during reboot, we  first ran CPUID with 0x4FFFFFFF and noted the number of exits before reboot  
<img width="649" alt="Screenshot 2023-12-17 at 9 33 44 PM" src="https://github.com/upasanakr/CMPE-283-VirtualTechnologies_Assignment-2and3/assets/37268397/9c648694-d7af-437c-bf07-2c0b6f6931e4">

We see, number of exits before reboot = 6400562  
Then we performed a reboot in inner VM and noted the number of exits after the reboot  
<img width="663" alt="Screenshot 2023-12-17 at 9 34 55 PM" src="https://github.com/upasanakr/CMPE-283-VirtualTechnologies_Assignment-2and3/assets/37268397/5abf2390-b316-44f2-998a-103bd84aeeff">

We see, the number of exits after reboot = 7855940

Hence, approximately 1455378 exits occurred during the reboot process. This is an approximate figure and may vary from system to system.
   
### 4. Of the exit types defined in the SDM, which are the most frequent? Least?
To verify this, we have used the test_top_exits.c file that is uploaded to the repository. We have run the CPUID with %eax = 0x4FFFFFFD and ecx ranging from 0 to 75. Below is the output:

<img width="336" alt="Screenshot 2023-12-17 at 9 49 13 PM" src="https://github.com/upasanakr/CMPE-283-VirtualTechnologies_Assignment-2and3/assets/37268397/efbf9416-fed1-464d-b153-7d68b3ba2b5e">
<img width="324" alt="Screenshot 2023-12-17 at 9 49 24 PM" src="https://github.com/upasanakr/CMPE-283-VirtualTechnologies_Assignment-2and3/assets/37268397/611b4ba1-6121-425d-a47e-4301359bd90f">

We observed that ecx 30 had the most number of exits followed by 28, 49, 10 and 32.  
Many ecx values had 0 exits. All of them can be considered least.
## Output Screenshots

Tested using the C file(test.c) uploaded in the repository.  
Running ./a.out will run the CPUID with %eax = 0x4FFFFFFF and %eax = 0x4FFFFFFE  
<img width="831" alt="Screenshot 2023-12-17 at 6 52 33 PM" src="https://github.com/upasanakr/CMPE-283-VirtualTechnologies_Assignment-2and3/assets/37268397/d0f9ccd7-2bf0-4c1f-a0ad-f8801e1ec45e">

Running ./a.out <ecx> will run CPUI with %eax = 0x4FFFFFFD and %eax = 0x4FFFFFFC and the provided ecx value. 
<img width="855" alt="Screenshot 2023-12-17 at 7 10 39 PM" src="https://github.com/upasanakr/CMPE-283-VirtualTechnologies_Assignment-2and3/assets/37268397/a09b539a-2398-4b71-9df7-0aed82d4cb79">

If the ecx is out of range or undefined, it will return 0's for %eax, %ebx, %ecx and it will return 0xFFFFFFFF for %edx  
<img width="820" alt="Screenshot 2023-12-17 at 7 41 54 PM" src="https://github.com/upasanakr/CMPE-283-VirtualTechnologies_Assignment-2and3/assets/37268397/b900515b-caed-40ef-8ec1-fa1cbce91800">


Corresponding logs in demsg,
<img width="855" alt="Screenshot 2023-12-17 at 7 10 39 PM" src="https://github.com/upasanakr/CMPE-283-VirtualTechnologies_Assignment-2and3/assets/37268397/daf73e52-80f7-4661-83e1-4973be1928e8">


<img width="836" alt="Screenshot 2023-12-17 at 7 32 20 PM" src="https://github.com/upasanakr/CMPE-283-VirtualTechnologies_Assignment-2and3/assets/37268397/b67a5274-c706-42eb-aca6-112024b26348">
