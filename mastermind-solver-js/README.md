This package provides JavaScript bindings for [a SAT-based Mastermind solver](https://github.com/bohlender/mastermind-solver).

After loading, the WASM module instance provides the methods of the [native API](https://github.com/bohlender/mastermind-solver/blob/master/mastermind-solver-cpp/src/api.h) in addition to `malloc` and `free`:
```javascript
import loadWasm from 'mastermind-solver-js'

const instance = await loadWasm()

const codeLength = 100
const solver = instance._Solver_ctor(6,codeLength)

const pArr1 = instance._malloc(Int32Array.BYTES_PER_ELEMENT*codeLength)
const arr1 = new Int32Array(instance.HEAP8.buffer, pArr1, codeLength)
arr1.set(Array(codeLength).fill(0))
instance._add_interaction(solver, pArr1, 2, 0)
instance._free(pArr1)

const pSecret = instance._malloc(Int32Array.BYTES_PER_ELEMENT*codeLength)
const ok = instance._solve(solver, pSecret) === 1
if(!ok) throw "Solver failed to return a solution."

const secret = new Int32Array(instance.HEAP8.buffer, pSecret, codeLength)
if(secret.filter(x => x === 0).length !== 2) throw `Result must contain exactly two zeros: ${secret}`

instance._free(pSecret)
instance._Solver_dtor(solver)
```