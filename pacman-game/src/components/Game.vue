<template>
    <canvas ref="gameCanvas" width="400" height="400"></canvas>
  </template>
  
  <script>
  export default {
    name: "Game",
    data() {
      return {
        canvas: null,
        ctx: null,
        pacman: {
          x: 50,
          y: 50,
          size: 20,
          speed: 2,
          direction: 'right',
        },
        keys: {},
        map: [
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
          [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
          [1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1],
          [1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1],
          [1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1],
          [1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1],
          [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
        ],
      };
    },
    mounted() {
      this.canvas = this.$refs.gameCanvas;
      this.ctx = this.canvas.getContext("2d");
      window.addEventListener("keydown", this.handleKeydown);
      window.addEventListener("keyup", this.handleKeyup);
      this.gameLoop();
    },
    methods: {
      handleKeydown(e) {
        this.keys[e.key] = true;
      },
      handleKeyup(e) {
        this.keys[e.key] = false;
      },
      movePacman() {
        if (this.keys["ArrowUp"]) this.pacman.y -= this.pacman.speed;
        if (this.keys["ArrowDown"]) this.pacman.y += this.pacman.speed;
        if (this.keys["ArrowLeft"]) this.pacman.x -= this.pacman.speed;
        if (this.keys["ArrowRight"]) this.pacman.x += this.pacman.speed;
      },
      drawMap() {
        const blockSize = 20;
        this.ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);
        for (let y = 0; y < this.map.length; y++) {
          for (let x = 0; x < this.map[y].length; x++) {
            if (this.map[y][x] === 1) {
              this.ctx.fillStyle = "blue";
              this.ctx.fillRect(x * blockSize, y * blockSize, blockSize, blockSize);
            }
          }
        }
      },
      drawPacman() {
        this.ctx.fillStyle = "yellow";
        this.ctx.beginPath();
        this.ctx.arc(this.pacman.x, this.pacman.y, this.pacman.size, 0.2 * Math.PI, 1.8 * Math.PI);
        this.ctx.lineTo(this.pacman.x, this.pacman.y);
        this.ctx.fill();
      },
      gameLoop() {
        this.movePacman();
        this.drawMap();
        this.drawPacman();
        requestAnimationFrame(this.gameLoop);
      },
    },
    beforeDestroy() {
      window.removeEventListener("keydown", this.handleKeydown);
      window.removeEventListener("keyup", this.handleKeyup);
    },
  };
  </script>
  
  <style scoped>
  canvas {
    border: 2px solid white;
    background-color: black;
  }
  </style>
  