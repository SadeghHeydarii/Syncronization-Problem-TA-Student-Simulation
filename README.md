# 👨‍🏫 Sleeping Teaching Assistant (TA) Problem - Multithreaded Simulation in C++

This project is a **multithreaded simulation in C++** of the classic **Sleeping Teaching Assistant problem**, implemented using:

- `pthread` threads  
- `mutex` for mutual exclusion  
- `condition_variable` for synchronization  
- `semaphores` to limit waiting chairs

---

## 📘 Problem Description

A teaching assistant (TA) helps students who come to their office. However:

- The TA can help **only one student at a time**  
- There are **5 chairs** outside the office for waiting students  
- If **all chairs are occupied**, students will **leave and try again later**  
- When **no students are waiting**, the TA goes to **sleep**  
- The TA wakes up when a student arrives  
- Simulation ends once **all students have been helped exactly once**

---

## ⚙️ How to Compile

Use `g++` with pthread support:

```bash
g++ -pthread main.cpp -o sleeping_ta
```

---

## ▶️ How to Run

Run the compiled file with number of students as argument:

```bash
./sleeping_ta <number_of_students>
```

Example:

```bash
./sleeping_ta 7
```

📝 **Note:** No further input is required during execution.

---

## 🪑 Key Features & Behavior

- **TA sleeps** when no students are present  
- **FIFO queue** of students using a circular buffer  
- **Semaphores** used to represent available chairs  
- **Student retries** if no chairs are available  
- **Simulation ends** when all students are helped once

---

## 💬 Example Messages & What They Mean

During execution, you may see messages like:

```bash
TA is sleeping
Student 2 found no chair and will come back later
Student 3 is getting help from TA
TA has helped all students. Exiting...
```

**Explanation:**

- `TA is sleeping` → No students are in queue; TA is idle  
- `Student X found no chair and will come back later` → All chairs full; student will retry  
- `Student Y is getting help from TA` → Student Y is currently being helped  
- `TA has helped all students. Exiting...` → Simulation successfully completed  

---

## 🧪 Sample Output

```bash
TA is sleeping
Student 1 is getting help from TA
Student 3 found no chair and will come back later
Student 2 is getting help from TA
Student 4 is getting help from TA
Student 3 is getting help from TA
Student 5 is getting help from TA
Student 6 is getting help from TA
Student 7 is getting help from TA
TA has helped all students. Exiting...
```

---

## 🧠 Concepts Involved

- Producer-Consumer pattern  
- Thread synchronization (mutex & condition variables)  
- Bounded Buffer (circular queue)  
- Resource management with semaphores  
- Thread-safe communication  
- Preventing race conditions and deadlocks  

---

## 🖥️ System Requirements

- POSIX-compliant OS (Linux / macOS)
- `g++` compiler with pthread support



