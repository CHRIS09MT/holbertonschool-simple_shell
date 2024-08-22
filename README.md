# __Simple Shell 🐚__
_A lightweight command line to interact with the operating system._

---

## __Description 📜__

_In this project, we aim to create a simple version of a shell, where a command line is generated that allows users to interact with the operating system._

---

## __How to Use 🛠️__

- __Line of command:__

    ```
    SimpleShell$ ls
    ```

---

### __Parts:__

- __Prompt 💻:__

    ```
    SimpleShell$ 
    ```

- __Command 📝:__

    ```
    ls
    ```

- __Output 📂:__

    ```
    [File1] [File2] [Directory1]
    ```

---

## __Command Examples 🎯__

### 1) `ls` 📁

- __Input:__

    ```
    SimpleShell$ ls
    ```

- __Output:__

    ```
    [File1] [File2] [Directory1]
    ```

_(Shows all files in the current directory)._

### 2) `clear` 🧹

- __Before Execution:__

    ```
    SimpleShell$ ls
    [File1]
    [File2]
    [Directory1]
    SimpleShell$
    ```

- __Input:__

    ```
    SimpleShell$ clear
    ```

- __Output:__

    ```
    SimpleShell$
    ```
_(The screen is cleared, and only the prompt is visible)._

### 3) `rm` 🗑️

- __Before Execution:__

    ```
    SimpleShell$ ls
    [File1]
    [File2]
    [Directory1]
    SimpleShell$
    ```

- __Input:__

    ```
    SimpleShell$ rm [File2]
    ```

- __Output:__

    ```
    SimpleShell$ rm [File2]
    SimpleShell$ ls
    [File1]
    [Directory1]
    SimpleShell$
    ```

_(Deletes a file from the current directory)._

### 4) `pwd` 📍

- __Input:__

    ```
    SimpleShell$ pwd
    ```

- __Output:__

    ```
    [Current-Path-User]
    ```

 _(This command prints the current working directory path)._

### 5) __`exit` And `Ctrl + D` 🚪__

- __Input:__

    ```
    SimpleShell$ exit
    ```

- __Output:__

    _`(The shell exits and the terminal session ends)`_

- __Alternative Input:__

    ```
    (Ctrl + D)
    ```

- __Output:__

    _`(The shell exits and the terminal session ends)`_

---

## __Installation ⚙️__

> [!IMPORTANT]
> _To install and set up Simple Shell, follow these steps:_

1. __Clone the repository 🖥️:__

   ```
   git clone https://github.com/sags7/holbertonschool-simple_shell.git
   ```

2. __Navigate to the project directory 📂:__

   ```
   cd holbertonschool-simple_shell
   ```

3. __Compile the source code 🛠️:__

   ```
   gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
   ```

4. __Run the shell 🚀:__

   ```
   ./hsh
   ```

---

## __Manual Installation 📖__

>[!IMPORTANT]
>_To install the manual for `Simple Shell` so you can access it using the `man` command, follow these steps:_

1. __Move the manual to the appropriate directory 📂:__

    ```
    sudo mv man_simple_shell /usr/share/man/man1/simple_shell.1
    ```

2. __Update the man database 🔄:__

    ```
    sudo mandb
    ```

3. __Access the manual 📜:__

    ```
    man simple_shell
    ```

---

## __Authors ✍️__

_Collaborators of the project._

- __Christopher Morales Torres__

    📧 christophermoralestorres06@gmail.com

- __Juan Sebastian Aramburo__

    📧 juansebastianaramburo@gmail.com