// بسم الله الرحمن الرحيم
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kthread.h>    // for kthreads
#include <linux/delay.h>      // for msleep
#include <linux/mutex.h>      // for mutexes

static struct task_struct *thread1;
static struct task_struct *thread2;

static DEFINE_MUTEX(lockA);
static DEFINE_MUTEX(lockB);

int thread_fn1(void *data) {
    pr_info("Thread 1 trying to acquire lock A ..\n");
    mutex_lock(&lockA);
    pr_info("Thread 1 acquired lock A \n");

    msleep(3000); // sleep 3 seconds

    pr_info("Thread 1 trying to acquire lock B ..\n");
    mutex_lock(&lockB);
    pr_info("Thread 1 acquired lock B \n");

    pr_info("Thread 1 in critical section\n");

    mutex_unlock(&lockB);
    mutex_unlock(&lockA);

    return 0;
}

int thread_fn2(void *data) {
    pr_info("Thread 2 trying to acquire lock B ..\n");
    mutex_lock(&lockB);
    pr_info("Thread 2 acquired lock B \n");

    msleep(3000); // sleep 3 seconds

    pr_info("Thread 2 trying to acquire lock A ..\n");
    mutex_lock(&lockA);
    pr_info("Thread 2 acquired lock A \n");

    pr_info("Thread 2 in critical section\n");

    mutex_unlock(&lockA);
    mutex_unlock(&lockB);

    return 0;
}

static int __init deadlock_init(void) {
    pr_info("Deadlock module loaded!\n");

    // Start kernel threads
    thread1 = kthread_run(thread_fn1, NULL, "thread1");
    thread2 = kthread_run(thread_fn2, NULL, "thread2");

    return 0;
}

static void __exit deadlock_exit(void) {
    pr_info("Deadlock module unloaded!\n");
}

module_init(deadlock_init);
module_exit(deadlock_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Deadlock example kernel module.");
