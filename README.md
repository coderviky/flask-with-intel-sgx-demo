# Flask WebApp : Addition of 2 Numbers using Intel SGX

"Flask WebApp: Addition of 2 Numbers using Intel SGX" is a project demo that leverages the power of Intel Software Guard Extensions (SGX) technology to securely perform addition of two numbers in a web application built with Flask, a popular web framework in Python.

This project demo aims to demonstrate how SGX can be utilized to perform secure computation within an enclave, protecting the confidentiality and integrity of sensitive data even in untrusted environments.

Users can input two numbers through a web interface, and the Flask webapp securely passes the numbers to an SGX enclave for addition. The result is then returned and displayed to the user, ensuring the privacy and security of the computation.

This project demo showcases the integration of Intel SGX technology into web applications using Flask, highlighting the potential of secure computation in protecting sensitive data in web-based scenarios.

<br/>
<br/>

## How to

First enable Intel SGX in BIOS/UEFI settings then install SGX Linux Drivers ([Guide](https://docs.scrt.network/secret-network-documentation/infrastructure/node-runners/node-setup/install-sgx)) and [Intel SGX Linux SDK](https://github.com/intel/linux-sgx) & [Intel SGX Linux PSW](https://github.com/intel/linux-sgx)

```bash
# generate files to run in sgx enclave
  make

# generate shared object files
  make so

# install Flask if not installed
  pip3 install Flask

# run Flask server
  python3 main.py

# clean generated binary files
  make clean
```

Go to http://127.0.0.1:5000/

Username - admin & Password - admin

<br/>
<br/>
<br/>
<br/>
