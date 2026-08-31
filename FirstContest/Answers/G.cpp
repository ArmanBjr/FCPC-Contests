// =============================================================================
// FCPC — Ferdowsi University Programming Contest
// Archive solution (reference answer)
// Year    : 2024
// Contest : Season 1 (First Contest)
// Problem : G
// Author  : Arman Bijari
// Repo    : https://github.com/ArmanBjr/FCPC-Contests
// =============================================================================

#include <cstdio>
#include <cstring>

const int MAXN = 101;
const int MAXR = 15;
const int MAXT = 602;
const int MAX_STANJA = 2 * MAXN + 2;

// pGol[ which_goalkeeper_has_ball ][ who_will_score ][ move_number ];
// pGol[ 0 ][ 1 ][ 1 ] is the probability that if team 0's goalkeeper receives the ball,
// on the first move they immediately score a goal for team 1.
double pGol[ 2 ][ 2 ][ MAXT ];

// pMir[ which_goalkeeper_has_ball ][ move_number ] is the probability that after
// move_number moves, no goal has been scored yet.
double pMir[ 2 ][ MAXT ];

// N is the number of players (including goalkeeper) per team
// T is the number of moves to be played
// R is the target number of goals (game ends at R)
int N, T, R;

// This class is responsible for reading accuracy and passing data,
// and generating the pGol and pMir arrays.
class Preprocess {
  // The state in preprocessing is P(entity, t), the probability that at
  // moment t, entity has the ball. Entity can be any player of both
  // teams or the goals. The goal is encoded as 2*N + TEAM
  // Player accuracy
  double matrix[ MAX_STANJA ][ MAX_STANJA ];

  // The number of states we're working with
  int matrix_size;

  // Reads accuracies and passing probabilities.
  void load() {
    int kard[2], kome;
    double p;
    memset(matrix, 0, sizeof matrix);
    for (int tim = 0; tim < 2; ++tim) {
      for (int id = 0; id < N; ++id) {
        // Probability that this player will now score a goal against the opponent.
        // The complementary probability is the probability he passes to the
        // opposing goalkeeper. (misses the goal)
        scanf("%lf%d%d", &p, kard + 0, kard + 1);
        // To whom can he pass and who can take the ball from him
        for (int protivnik = 0; protivnik < 2; ++protivnik) {
          for (int k = 0; k < kard[protivnik]; ++k) {
            scanf("%d", &kome);
            matrix
              [ tim * N + id ]
              [ (protivnik ^ tim) * N + kome - 1 ]
                += 1. / (1+kard[0]+kard[1]);
          }
        }
        // Add shot outcomes.
        matrix[ tim * N + id ][ 2 * N + (!tim) ] += p / (1+kard[0]+kard[1]);
        matrix[ tim * N + id ][ (!tim) * N + 0 ] += (1-p) / (1+kard[0]+kard[1]);
      }
    }
    /*
    for (int i = 0; i < matrix_size; ++i) {
      for (int j = 0; j < matrix_size; ++j) {
        printf("%6.3lf", matrix[i][j]);
      }
      printf("\n");
    }
    */
  }

  // Iterate probabilities in the matrix and generate pGol
  void solve() {
    for (int tim = 0; tim < 2; ++tim) {
      double p[ 2 ][ MAX_STANJA ];
      int staro = 0;
      memset( p[ staro ], 0, sizeof p[0] );
      p[ staro ][ tim * N ] = 1;
      // TODO, complexity can be N^3 here: matrix multiplications
      for (int t = 0; t < T + 1; ++t) {
        // Update result
        pGol[ tim ][ 0 ][ t ] = p[ staro ][ 2 * N + 1 ];
        pGol[ tim ][ 1 ][ t ] = p[ staro ][ 2 * N + 0 ];
        // Compute new probabilities based on previous ones
        memset( p[!staro], 0, sizeof p[0] );
        for (int k = 0; k < matrix_size; ++k)
          for (int j = 0; j < matrix_size; ++j)
            p[ !staro ][ j ] += p[ staro ][ k ] * matrix[ k ][ j ];
        // Swap old and new
        staro = !staro;
      }
    }
  }

  // Must generate pMir
  void post() {
    for (int tim = 0; tim < 2; ++tim) {
      double mir = 1;
      for (int t = 0; t < T + 1; ++t) {
        mir -= pGol[ tim ][ 0 ][ t ];
        mir -= pGol[ tim ][ 1 ][ t ];
        pMir[ tim ][ t ] = mir;
      }
    }
  }

 public:
  Preprocess() {
    matrix_size = 2 * N + 2;
    load();
    solve();
    post();
  }
};

void load() {
  scanf("%d%d%d", &N, &R, &T);
  new Preprocess();
}

double dp[ MAXR ][ MAXR ][ 2 ][ MAXT ];

// Precompute:
// R^2 * 2 * T * 2 * T
// == 4 (RT)^2 == 4 * 36 * 10^6 == 10^8

// Probability that at move t, team tko has scored for r1:r2
// At time 0, team 1 has scored for 0:0, so team 0 gets the ball.
double solve(int r1, int r2, int tko, int t) {
  if (r1 < 0 || r2 < 0 || t < 0) return 0;
  if (!r1 && !r2 && tko && !t) return 1;
  double &sol = dp[ r1 ][ r2 ][ tko ][ t ];
  if (sol != -1) return sol;

  // Put r1 and r2 into an array for easier handling.
  int rezultat[2] = {r1, r2};
  // The previous result is unique (the team who just scored had one less goal).
  // If negative, probability is zero due to the first line.
  rezultat[tko] -= 1;
  sol = 0;

  // The previous result is unique (let's call it R), stored in rezultat array.
  // The probability that at move t, team tko has scored for r1:r2
  // can be broken down by cases of who scored the previous goal (for R).
  for (int tko_zabio_prosli = 0; tko_zabio_prosli < 2; ++tko_zabio_prosli) {
    // Further split by the moment that previous goal was scored.
    for (int prosli_t = 0; prosli_t < t; ++prosli_t) {
      sol +=
        solve(rezultat[0], rezultat[1], tko_zabio_prosli, prosli_t) *
        pGol[ !tko_zabio_prosli ][ tko ][ t - prosli_t ];
    }
  }

  return sol;
}

// Probability the game ended with r1:r2. Must not be r1==r2==K
double read(int r1, int r2) {
  double sol = 0;
  int rezultat[2] = {r1, r2};
  // If there were no goals, that's a special case.
  if (!r1 && !r2) {
    return pMir[ 0 ][ T ];
  }
  // If the game stopped because one team reached R goals
  if (r1 == R || r2 == R) {
    // Pick the winner (only one).
    for (int pobjednik = 0; pobjednik < 2; ++pobjednik) {
      if (rezultat[pobjednik] != R) continue;
      for (int t = 0; t <= T; ++t)
        sol += solve(r1, r2, pobjednik, t);
    }
  } else {
    // Split by which team scored the last goal.
    for (int zadnji_gol = 0; zadnji_gol < 2; ++zadnji_gol) {
      // Split by when that last goal happened.
      for (int t = 0; t <= T; ++t) {
        sol += solve(rezultat[0], rezultat[1], zadnji_gol, t)
          * pMir[ !zadnji_gol ][ T - t ];
      }
    }
  }
  return sol;
}

int main() {
  for (int i = 0; i < MAXR; ++i)
    for (int j = 0; j < MAXR; ++j)
      for (int k = 0; k < 2; ++k)
        for (int t = 0 ; t < MAXT; ++t)
          dp[i][j][k][t] = -1;
  load();
  double sum = 0;
  for (int a = 0; a <= R; ++a) {
    for (int b = 0; b <= R; ++b) {
      if (a == R && b == R) continue;
      printf("%.10lf\n", read(a, b));
      sum += read(a, b);
    }
  }
  return 0;
}
