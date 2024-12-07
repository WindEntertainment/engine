import * as math from 'math';

const re = /ab+c/i;

export class Player {
  constructor() {
    this.x = 3;
  }

  add(a, b, c = 5) {
    return a + b + c;
  }

  async update() {
    let y = 255;
    let z = 100;

    // Simulate asyncAdd functionality
    let response = await math.asyncAdd(1, 2);

    if (!response) {
      // throw new Error('Error');
      throw new Error(`${y}`);
    }

    this.x = (this.x * (y - z)) / -(100 + this.x);
  }

  getName() {
    return 'NeutrinoZh';
  }

  // private field simulation
  _canMove = false;
  _string = 'LOONG STRING';
}

export class Board {
  async example(a) {
    let i = 0;
    for (i = 0; i < 10; ++i) {
      i += 1;
    }

    while (false || (true && a)) {
      i = 10;
      if (false) {
      } else {
        continue;
      }
    }

    if (true) {
      return true;
    }
  }
}

export function add(a, b, c = 5) {
  return 132;
}

// Create instances of classes
const c = new Player();
const s = new Board();

export async function outerFunction(a, b, c = 5) {
  return 132;
}
