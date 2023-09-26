#include "tx_api.h"

#define NUM_THREADS 4
#define QUEUE_SIZE 5

TX_THREAD traffic_thread1;
TX_THREAD traffic_thread2;
TX_THREAD traffic_thread3;
TX_THREAD traffic_controller_thread;

TX_SEMAPHORE traffic_semaphore;
TX_QUEUE traffic_queue;

ULONG traffic_data[QUEUE_SIZE];

void traffic_thread_entry(ULONG thread_input)
{
    ULONG my_id = thread_input;
    ULONG vehicle_id = 1;

    while (1)
    {
        // Simula a chegada de um veículo
        ULONG vehicle = my_id * 1000 + vehicle_id;

        // Tenta adquirir o semáforo de tráfego
        if (tx_semaphore_get(&traffic_semaphore, TX_WAIT_FOREVER) == TX_SUCCESS)
        {
            // Insere o veículo na fila
            if (tx_queue_send(&traffic_queue, &vehicle, sizeof(ULONG)) == TX_SUCCESS)
            {
                // Libera o semáforo de tráfego
                tx_semaphore_put(&traffic_semaphore);

                // Incrementa o ID do veículo
                vehicle_id++;

                // Simula o veículo atravessando o cruzamento
                tx_thread_sleep(1);
            }
        }
    }
}

void traffic_controller_thread_entry(ULONG thread_input)
{
    ULONG vehicle;

    while (1)
    {
        // Espera até que haja veículos na fila
        if (tx_queue_receive(&traffic_queue, &vehicle, TX_WAIT_FOREVER) == TX_SUCCESS)
        {
            // Controla o tráfego, por exemplo, permitindo que veículos de uma direção passem
            // enquanto outros aguardam

            // Simula o controle de tráfego
            tx_thread_sleep(2);

            // Libera o semáforo de tráfego para permitir que outro veículo entre
            tx_semaphore_put(&traffic_semaphore);

            // Simula o veículo saindo do cruzamento
            tx_thread_sleep(1);
        }
    }
}

int main(void)
{
    tx_kernel_enter();

    // Inicializa o semáforo de tráfego
    tx_semaphore_create(&traffic_semaphore, "Traffic Semaphore", 1);

    // Inicializa a fila de tráfego
    tx_queue_create(&traffic_queue, "Traffic Queue", sizeof(ULONG), traffic_data, QUEUE_SIZE);

    // Cria threads de tráfego
    tx_thread_create(&traffic_thread1, "Traffic Thread 1", traffic_thread_entry, 1, &traffic_thread1_stack, THREAD_STACK_SIZE, 1, 1, TX_NO_TIME_SLICE, TX_AUTO_START);
    // Crie outras threads de tráfego aqui

    // Crie a thread do controlador de tráfego
    tx_thread_create(&traffic_controller_thread, "Traffic Controller", traffic_controller_thread_entry, 0, &traffic_controller_thread_stack, THREAD_STACK_SIZE, 1, 1, TX_NO_TIME_SLICE, TX_AUTO_START);

    return 0;
}
