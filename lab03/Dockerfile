FROM ubuntu:20.04

# Prevent interactive prompts during package install
ENV DEBIAN_FRONTEND=noninteractive  

# Install SSH server, MPI, compiler
RUN apt-get update && apt-get install -y \
    openssh-server \
    openmpi-bin openmpi-common libopenmpi-dev \
    build-essential

# Create mpiuser with password mpiuser
RUN useradd -ms /bin/bash mpiuser && echo "mpiuser:mpiuser" | chpasswd

# Setup SSH for mpiuser
RUN mkdir -p /home/mpiuser/.ssh && \
    ssh-keygen -t rsa -f /home/mpiuser/.ssh/id_rsa -q -N "" && \
    cat /home/mpiuser/.ssh/id_rsa.pub >> /home/mpiuser/.ssh/authorized_keys && \
    chown -R mpiuser:mpiuser /home/mpiuser/.ssh && \
    chmod 700 /home/mpiuser/.ssh && \
    chmod 600 /home/mpiuser/.ssh/id_rsa /home/mpiuser/.ssh/authorized_keys

# Start script to launch SSH daemon
RUN echo '#!/bin/bash\n\
mkdir -p /run/sshd\n\
ssh-keygen -A\n\
exec /usr/sbin/sshd -D\n' > /start.sh && chmod +x /start.sh

EXPOSE 22
CMD ["/start.sh"]
