# WaitAbort-In-RTOS-AZURE

Incluímos a biblioteca tx_api.h, que é a biblioteca principal para o Azure RTOS.

Definimos constantes como NUM_THREADS e QUEUE_SIZE para configurar o número de threads de tráfego e o tamanho da fila de tráfego.

Declaramos várias variáveis globais, incluindo threads (traffic_thread1, traffic_thread2, traffic_thread3, traffic_controller_thread), um semáforo (traffic_semaphore) e uma fila (traffic_queue) para simular o controle de tráfego.

Criamos duas funções de entrada de thread: traffic_thread_entry e traffic_controller_thread_entry. Essas funções serão executadas quando as threads forem criadas. traffic_thread_entry simula a chegada de veículos nas vias de tráfego, enquanto traffic_controller_thread_entry controla o tráfego no cruzamento.

Dentro da função traffic_thread_entry, cada thread de tráfego simula a chegada de veículos, adquire um semáforo de tráfego, insere o veículo na fila, libera o semáforo e, em seguida, simula o veículo atravessando o cruzamento.

Dentro da função traffic_controller_thread_entry, a thread do controlador de tráfego aguarda até que haja veículos na fila, controla o tráfego (por exemplo, permitindo que veículos de uma direção passem enquanto outros aguardam), libera o semáforo de tráfego para permitir que outro veículo entre e, em seguida, simula o veículo saindo do cruzamento.

No main(), inicializamos o kernel do Azure RTOS com tx_kernel_enter().

Criamos um semáforo de tráfego com tx_semaphore_create() e uma fila de tráfego com tx_queue_create().

Criamos threads de tráfego usando tx_thread_create(). Cada thread de tráfego executa a função traffic_thread_entry e simula a chegada de veículos em vias diferentes.

Criamos a thread do controlador de tráfego usando tx_thread_create(). Ela executa a função traffic_controller_thread_entry e controla o tráfego no cruzamento.

Este código simula um sistema de controle de tráfego com várias threads de veículos e um controlador de tráfego, usando semáforos e filas para sincronização. Lembre-se de que este é apenas um exemplo e pode ser adaptado e ajustado conforme necessário para atender aos requisitos específicos do seu trabalho de faculdade.
