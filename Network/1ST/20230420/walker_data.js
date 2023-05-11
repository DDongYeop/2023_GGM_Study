const { Worker, isMainThread, parentPort, workerData } = require('worker_threads');

if (isMainThread) // 부모 스레드
{
    const threads = new Set();
    threads.add(new Worker(__filename, {
        workerData: {name: '김민수'},
    }))
    threads.add(new Worker(__filename, {
        workerData: {name: '박부성'},
    }))

    for (let worker of threads)
    {
        worker.on('message', message =>
        {
            console.log('from worker: ', message);
        });
        worker.on('exit', () =>
        {
            threads.delete(worker);
            if (threads.size == 0)
            {
                console.log('회사 문 닫습니다.');
            }
        });
    }
}
else //워커일 때  
{
    const data = workerData;
    parentPort.postMessage(data.name);
}
