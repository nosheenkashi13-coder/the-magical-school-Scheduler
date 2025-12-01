# Pseudocode for School Timetable Scheduler

----------------------------------------------------
FUNCTION AddTeacher()
----------------------------------------------------
INPUT: teacherID, name, subject, availability
CREATE newTeacher node
SET newTeacher.id = teacherID
SET newTeacher.name = name
SET newTeacher.subject = subject
SET newTeacher.availability = availability
SET newTeacher.next = NULL
SET newTeacher.prev = NULL

IF headTeacher IS NULL THEN
    headTeacher = newTeacher
    tailTeacher = newTeacher
ELSE
    tailTeacher.next = newTeacher
    newTeacher.prev = tailTeacher
    tailTeacher = newTeacher
END IF

DISPLAY "Teacher added successfully"
END FUNCTION
----------------------------------------------------
FUNCTION AddClass()
----------------------------------------------------
INPUT: className, subject
CREATE classRoom object
SET classRoom.className = className
SET classRoom.subject = subject
ENQUEUE classRoom INTO classQueue
DISPLAY "Class added to queue"
END FUNCTION
----------------------------------------------------
FUNCTION AddClass()
----------------------------------------------------
INPUT: className, subject
CREATE classRoom object
SET classRoom.className = className
SET classRoom.subject = subject
ENQUEUE classRoom INTO classQueue
DISPLAY "Class added to queue"
END FUNCTION
----------------------------------------------------
FUNCTION CheckConflict(teacherName, subject)
----------------------------------------------------
CREATE tempStack = scheduleStack

WHILE tempStack IS NOT EMPTY
    SET current = TOP(tempStack)
    POP tempStack

    IF current.teacherName == teacherName AND
       current.subject == subject THEN
         RETURN TRUE
    END IF
END WHILE

RETURN FALSE
END FUNCTION
----------------------------------------------------
FUNCTION GenerateSchedule()
----------------------------------------------------
IF headTeacher IS NULL OR classQueue IS EMPTY THEN
    DISPLAY "Need at least one teacher and one class"
    RETURN
END IF

SET currentTeacher = headTeacher

WHILE classQueue IS NOT EMPTY
    DEQUEUE nextClass FROM classQueue

    IF CheckConflict(currentTeacher.name, nextClass.subject) THEN
        DISPLAY "Conflict for " + currentTeacher.name
    ELSE
        CREATE scheduleEntry
        SET scheduleEntry.teacherName = currentTeacher.name
        SET scheduleEntry.className = nextClass.className
        SET scheduleEntry.subject = nextClass.subject
        PUSH scheduleEntry INTO scheduleStack
        DISPLAY "Assigned " + currentTeacher.name + " to " + nextClass.className
    END IF

    MOVE currentTeacher = currentTeacher.next
    IF currentTeacher IS NULL THEN
        SET currentTeacher = headTeacher
    END IF
END WHILE

DISPLAY "Schedule generation completed"
END FUNCTION
----------------------------------------------------
FUNCTION ViewTimetable()
----------------------------------------------------
IF scheduleStack IS EMPTY THEN
    DISPLAY "Timetable is empty"
    RETURN
END IF

CREATE tempStack = scheduleStack

WHILE tempStack IS NOT EMPTY
    SET entry = TOP(tempStack)
    POP tempStack
    DISPLAY entry.teacherName + " teaches " +
            entry.className + " (" + entry.subject + ")"
END WHILE

END FUNCTION
