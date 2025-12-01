# Data Structure Planning Table

| Operation                        | Data Structure Used | Reason for Choosing the DS |
|----------------------------------|---------------------|-----------------------------|
| Add New Teacher                  | Doubly Linked List  | Allows easy insertion, updating and deletion of teacher records from any position |
| View Teachers (Forward/Reverse)  | Doubly Linked List  | Supports traversal from both directions using next and prev pointers |
| Add Class to be Scheduled        | Queue               | Classes must be assigned in the exact order they are added (FIFO) |
| Generate Schedule (Assign Teachers to Classes) | Stack | Stores timetable entries in reverse chronological order so the latest assignment appears first |
| Undo / Detect Instructor Conflict | Stack (Search)     | Stack helps track history of schedule assignments and detect if a teacher is already assigned to the same subject |
| View Final Timetable             | Stack               | Allows viewing schedule in LIFO order so the most recent scheduling is shown first |
