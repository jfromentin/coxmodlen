#include <ostream>
#include <thread>

#include "coxeter_enumerator.hpp"
#include "results.hpp"

static const size_t nb_threads = 30;
static const Int N = 10;
static const char T = 'A';
static const Int k = 2;
static const Int h = 1;

struct Task {
  size_t a;
  size_t b;
};

struct Data {
  Task* tasks;
  size_t nb_tasks;
  Results res;
};

void* work(void* ptr) {
  Data* data = (Data*)ptr;
  CoxeterEnumerator<T, N> enumerator;
  for (int i = 0; i < data->nb_tasks; ++ i) {
    CoxeterEnumerator<T, N> enumerator(data->tasks[i].a, data->tasks[i].b);
    enumerator.init();
    do{
      auto x = enumerator.get();
      size_t l = x.length(k, h);
      data->res.add(l);
    }while(enumerator.next());
  }
  pthread_exit(NULL);
}

void add_task(Data& data, size_t a, size_t b) {
  data.tasks[data.nb_tasks].a = a;
  data.tasks[data.nb_tasks].b = b;
  ++ data.nb_tasks;
}

int main() {
  Int R;
  switch(T){
  case 'A':
    R = N + 1;
    break;
  case 'B':
  case 'D':
    R = N;
    break;
  default:
    cerr << "Not yet defined" << endl;
    exit(0);
  };
  
  size_t nb_tasks = R * (R - 1);
  cout << " Coxeter type: " << T << endl;
  cout << " Coxeter rank: " << N << endl;
  cout << " Permumtation rank: " << R << endl;
  cout << " Number of tasks: " << nb_tasks << endl;
  cout << " Number of threads: " << nb_threads << endl;
  size_t max_nb_tasks = (nb_tasks + nb_threads - 1) / nb_threads;
  cout << " Max number of tasks by thread: " << max_nb_tasks << endl;
  Data datas[nb_threads];
  for (size_t i = 0; i < nb_threads; ++ i) {
    datas[i].tasks = new Task[max_nb_tasks];
    datas[i].nb_tasks = 0;
  }
  size_t id = 0;
  for (size_t a = 0; a < R; ++ a) {
    for (size_t b = 0; b < R; ++ b) {
      if (a != b) {
	size_t t = id % nb_threads;
	add_task(datas[t], a, b);
	++ id;
      }
    }
  }
  pthread_t thread_id[nb_threads];
  cout << "> Launch threads" << endl;
  for (size_t i = 0; i < nb_threads; ++ i) {
    int err = pthread_create(&thread_id[i], NULL, work, &datas[i]);
  }
  for (size_t i = 0; i < nb_threads; ++ i) {
    pthread_join(thread_id[i], NULL);
  }
  /*  cout << "> Gather results" << endl;
  size_t total = 0;
  size_t res[ResSize];
  for (int i = 0; i < ResSize; ++ i) res[i] = 0;
  for (size_t i = 0; i < nb_threads; ++ i) {
    total += datas[i].total;
    for (int j = 0; j < ResSize; ++ j) res[j] += datas[i].res[j];
  }
  cout << " Total = " << total << " vs " << Asize << endl;
  cout << " -> [" << res[0];
  for (int i = 1; i < ResSize; ++ i) {
    cout << ',' << res[i];
  }
  cout << ']' << endl;*/
 
}
