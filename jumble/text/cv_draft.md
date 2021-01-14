# About me (WIP, DRAFT)

I am a perpetually improving Software Engineer with a bachelor degree in applied mathematics.

My biggest professional motivation is to create robust software with clean architecture, clean design and clean code.

Recently I've got fond of philosophy: a programmer does not have a goal, only the way.
This practically means that I always learn and will never stop.
And it renders my current state rather meamingless, because what I don't know today I will do tomorrow and so on and on.

## Projects
All projects I took part in at this point, except academic one, are managed by Agile methologies with 1-2 week sprints.
Maintenance tasks (various bug fixes and minor impovements) usually take from 4 hours up to three days, rarely more.
Significant improvements take 1-2 weeks.

### Pearlchain (Pearlchain)
Stack: Java, Spring, Hibernate.

The goal of the project is to provide Enterprise Resource Planning (ERP) solution for production of higly customized products,
taking into account real-time manufacturing capacities.

At the beginning of the project all my tasks were maintenance,
but once I've got used to the project, its philosophy and key concepts, I started to do refactoring and redesign of different systems.

My favorite task was to replace old naive implementation of in-house Domain-Specific Language (DSL) with a new one
which would allow easier maintenance and extension of the said DSL.
Original estimation was two weeks, but it took me three times more to pull it off and I don't regret a single day spent on this task.
First of all, I decoupled the old subsystem from the other system and designed a narrow interface.
Only using this interface the other code can communicate with the DSL subsystem.
This allowed me to isolate my changes from the other code and hide implementation details behind the interface.

It was the first time when I was using principles of R. C. Martin's clean architecture on such scale and it was great,
because benifits of such approach soon were proven to be useful.

That task left me exhausted so I decided to step back a little. Needed to recover,
and to get an overview of my previous career, read books and craft my pet projects to test new concepts.

### Naumen Service Desk (Naumen)
Stack: Java, Spring, Hibernate

The goal of the project is automation of management process in IT and service maintenance on production.

I was an intern and did maintenance tasks and minor improvements.
This was the first project where I've seen three-layered architecture in action and though I was just an intern and worked for a short period of time,
it was very valuable experience for me and I've learned a lot about industry-level development.

### Graduation Project (Chelyabinsk State University)
TBA

### Electronic Educational Systems (BARS Group)
Stack: Python, Django ORM

The goal of the project is to automate processes in Russian education system.

Most of the time I did maintenance. Once upon a time I got a bigger improvement task and failed it
(not completely; I produced required solution, but took too much time). Then another one.
After several failures all I did was maintenance and writing of unit-tests.

I stuck in routine tasks, stuck with my personal development,
and it didn't feel like I add enough value to the project.
In this situation the obvious decision was to move over, so I did.


### Db2 Cloning Tool (Complex Systems)
Stack: High-Level Assembly (HLASM), bare IBM hardware and a bit of C/C++.

The goal of the project is to make possible cloning various Db2 subsystems with minimal (or no) downtime.

Because this project is written with low-level language, it has much longer 4-week sprints.
Usual maintenance tasks like  bugfixes and minor improvements took a whole working week to make and significant improvements were made within a month or more.

Here for the first 3-4 weeks I learned HLASM and basic IBM mainframe workflow.
Later and till the end of my work with this project all I did was mantenance and bug reporting.

In general, I liked to work with machine language and bare metal,
but at the time IBM was withdrawing all development from Russia,
so I have had to look for another job.

## Prominent reading
### Clean Coder by Robert C. Martin
### Clean Architechture by Robert C. Martin
### Code Complete by Steve McConnell (Ongoing)
### Java. A Beginner's Guide by Herbert Schildt (Ongoing)
