<template>
  <canvas ref="gameCanvas"></canvas>
</template>

<script>
export default {
  name: "PacmanGame",
  data() {
    return {
      canvas: null,
      ctx: null,
      pacman: {
        x: 30,
        y: 30,
        size: 9, // 减小吃豆人的尺寸
        speed: 0.5, // 进一步降低速度
        direction: 'right',
      },
      keys: {},
      map: [
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1],
        [1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1],
        [1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1],
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1],
        [1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1],
        [1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1],
        [1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1],
        [1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1],
        [1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1],
        [1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1],
        [1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1],
        [1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1],
        [1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1],
        [1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1],
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1],
        [1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1],
        [1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1],
        [1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1],
        [1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1],
        [1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1],
        [1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1],
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1],
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
      ],
      gamepad: null,
      gamepadConnected: false,
      ghosts: [
        { x: 140, y: 140, color: 'red', speed: 0.25, direction: 'up' },
        { x: 160, y: 140, color: 'pink', speed: 0.25, direction: 'left' },
        { x: 180, y: 140, color: 'cyan', speed: 0.25, direction: 'down' },
        { x: 200, y: 140, color: 'orange', speed: 0.25, direction: 'right' },
      ],
      score: 0,
      blockSize: 20,
    };
  },
  mounted() {
    this.canvas = this.$refs.gameCanvas;
    this.ctx = this.canvas.getContext("2d");
    this.resizeCanvas();
    window.addEventListener("resize", this.resizeCanvas);
    window.addEventListener("keydown", this.handleKeydown);
    window.addEventListener("keyup", this.handleKeyup);
    window.addEventListener("gamepadconnected", this.handleGamepadConnected);
    window.addEventListener("gamepaddisconnected", this.handleGamepadDisconnected);
    this.initializeGameElements();
    this.gameLoop();
  },
  methods: {
    handleKeydown(e) {
      this.keys[e.key] = true;
    },
    handleKeyup(e) {
      this.keys[e.key] = false;
    },
    handleGamepadConnected(e) {
      console.log("Gamepad connected:", e.gamepad.id);
      this.gamepadConnected = true;
    },

    handleGamepadDisconnected(e) {
      console.log("Gamepad disconnected:", e.gamepad.id);
      this.gamepadConnected = false;
    },

    updateGamepadState() {
      if (this.gamepadConnected) {
        const gamepads = navigator.getGamepads();
        this.gamepad = gamepads[0]; // 使用第一个连接的手柄
      }
    },

    movePacman() {
      let newX = this.pacman.x;
      let newY = this.pacman.y;

      // 处理键盘输入
      if (this.keys["ArrowUp"]) {
        newY -= this.pacman.speed;
        this.pacman.direction = 'up';
      }
      if (this.keys["ArrowDown"]) {
        newY += this.pacman.speed;
        this.pacman.direction = 'down';
      }
      if (this.keys["ArrowLeft"]) {
        newX -= this.pacman.speed;
        this.pacman.direction = 'left';
      }
      if (this.keys["ArrowRight"]) {
        newX += this.pacman.speed;
        this.pacman.direction = 'right';
      }

      // 处理手柄输入
      if (this.gamepadConnected && this.gamepad) {
        const threshold = 0.2;
        const axisX = this.gamepad.axes[0];
        const axisY = this.gamepad.axes[1];

        if (axisY < -threshold) {
          newY -= this.pacman.speed;
          this.pacman.direction = 'up';
        }
        if (axisY > threshold) {
          newY += this.pacman.speed;
          this.pacman.direction = 'down';
        }
        if (axisX < -threshold) {
          newX -= this.pacman.speed;
          this.pacman.direction = 'left';
        }
        if (axisX > threshold) {
          newX += this.pacman.speed;
          this.pacman.direction = 'right';
        }
      }

      // 确保吃豆人不会移出地图
      newX = Math.max(this.pacman.size, Math.min(newX, this.canvas.width - this.pacman.size));
      newY = Math.max(this.pacman.size, Math.min(newY, this.canvas.height - this.pacman.size));

      // 检查墙壁碰撞
      if (!this.checkWallCollision(newX, this.pacman.y)) {
        this.pacman.x = newX;
      }
      if (!this.checkWallCollision(this.pacman.x, newY)) {
        this.pacman.y = newY;
      }
    },
    drawMap() {
      this.ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);
      for (let y = 0; y < this.map.length; y++) {
        for (let x = 0; x < this.map[y].length; x++) {
          if (this.map[y][x] === 1) {
            this.ctx.fillStyle = "blue";
            this.ctx.fillRect(x * this.blockSize, y * this.blockSize, this.blockSize, this.blockSize);
          }
        }
      }
    },
    drawPacman() {
      this.ctx.fillStyle = "yellow";
      this.ctx.beginPath();
      let startAngle, endAngle;
      switch (this.pacman.direction) {
        case 'up':
          startAngle = 1.75 * Math.PI;
          endAngle = 1.25 * Math.PI;
          break;
        case 'down':
          startAngle = 0.75 * Math.PI;
          endAngle = 0.25 * Math.PI;
          break;
        case 'left':
          startAngle = 1.25 * Math.PI;
          endAngle = 0.75 * Math.PI;
          break;
        case 'right':
        default:
          startAngle = 0.25 * Math.PI;
          endAngle = 1.75 * Math.PI;
          break;
      }
      this.ctx.arc(this.pacman.x, this.pacman.y, this.pacman.size, startAngle, endAngle);
      this.ctx.lineTo(this.pacman.x, this.pacman.y);
      this.ctx.fill();
    },
    checkWallCollision(x, y) {
      const gridX = Math.floor(x / this.blockSize);
      const gridY = Math.floor(y / this.blockSize);
      return this.map[gridY] && this.map[gridY][gridX] === 1;
    },
    moveGhosts() {
      this.ghosts.forEach(ghost => {
        let newX = ghost.x;
        let newY = ghost.y;

        switch (ghost.direction) {
          case 'up':
            newY -= ghost.speed;
            break;
          case 'down':
            newY += ghost.speed;
            break;
          case 'left':
            newX -= ghost.speed;
            break;
          case 'right':
            newX += ghost.speed;
            break;
        }

        // 检查墙壁碰撞
        if (!this.checkWallCollision(newX, newY)) {
          ghost.x = newX;
          ghost.y = newY;
        } else {
          // 如果遇到墙壁，选择一个新的可行方向
          const possibleDirections = this.getPossibleDirections(ghost);
          if (possibleDirections.length > 0) {
            const oppositeDirection = this.getOppositeDirection(ghost.direction);
            const filteredDirections = possibleDirections.filter(dir => dir !== oppositeDirection);
            ghost.direction = filteredDirections[Math.floor(Math.random() * filteredDirections.length)];
          }
        }
      });
    },

    getPossibleDirections(ghost) {
      const directions = [];
      const { x, y } = ghost;
      const speed = ghost.speed;

      if (!this.checkWallCollision(x, y - speed)) directions.push('up');
      if (!this.checkWallCollision(x, y + speed)) directions.push('down');
      if (!this.checkWallCollision(x - speed, y)) directions.push('left');
      if (!this.checkWallCollision(x + speed, y)) directions.push('right');

      return directions;
    },

    getOppositeDirection(direction) {
      switch (direction) {
        case 'up': return 'down';
        case 'down': return 'up';
        case 'left': return 'right';
        case 'right': return 'left';
      }
    },

    checkGhostCollision() {
      const pacmanCenterX = this.pacman.x;
      const pacmanCenterY = this.pacman.y;
      
      return this.ghosts.some(ghost => {
        const distance = Math.sqrt(
          Math.pow(pacmanCenterX - ghost.x, 2) + Math.pow(pacmanCenterY - ghost.y, 2)
        );
        return distance < this.pacman.size * 2;
      });
    },
    checkDotCollision() {
      const pacmanCenterX = this.pacman.x;
      const pacmanCenterY = this.pacman.y;
      
      this.ghosts = this.ghosts.filter(ghost => {
        const distance = Math.sqrt(
          Math.pow(pacmanCenterX - ghost.x, 2) + Math.pow(pacmanCenterY - ghost.y, 2)
        );
        if (distance < this.pacman.size) {
          this.score += 10;
          return false;
        }
        return true;
      });
    },
    gameLoop() {
      this.updateGamepadState();
      this.movePacman();
      this.moveGhosts();
      this.checkDotCollision();
      
      if (this.checkGhostCollision()) {
        alert("Game Over! Your score: " + this.score);
        this.resetGame();
        return;
      }
      
      this.drawMap();
      this.drawPacman();
      this.drawGhosts();
      this.drawScore();
      requestAnimationFrame(this.gameLoop);
    },
    drawGhosts() {
      this.ghosts.forEach(ghost => {
        this.ctx.fillStyle = ghost.color;
        this.ctx.beginPath();
        this.ctx.arc(ghost.x, ghost.y, this.pacman.size, 0, 2 * Math.PI);
        this.ctx.fill();
      });
    },
    drawScore() {
      this.ctx.fillStyle = 'white'; // 改变分数颜色以提高对比度
      this.ctx.font = '20px Arial';
      this.ctx.fillText(`Score: ${this.score}`, 10, this.canvas.height + 30); // 将分数显示在迷宫外
    },
    resetGame() {
      // 重置游戏状态
      this.initializeGameElements();
      this.ghosts = [
        { x: 200, y: 150, color: 'red', speed: 0.25, direction: 'up' },
        { x: 160, y: 140, color: 'pink', speed: 0.25, direction: 'left' },
        { x: 180, y: 140, color: 'cyan', speed: 0.25, direction: 'down' },
        { x: 200, y: 140, color: 'orange', speed: 0.25, direction: 'right' },
      ];
      this.score = 0;
      this.gameLoop();
    },
    resizeCanvas() {
      const aspectRatio = this.map[0].length / this.map.length;
      const maxWidth = window.innerWidth * 0.9;
      const maxHeight = window.innerHeight * 0.9;
      let width = maxWidth;
      let height = width / aspectRatio;

      if (height > maxHeight) {
        height = maxHeight;
        width = height * aspectRatio;
      }

      this.canvas.width = width;
      this.canvas.height = height;
      this.blockSize = width / this.map[0].length;
      this.adjustGameElements();
    },
    adjustGameElements() {
      // 调整吃豆人和幽灵的位置和大小
      this.pacman.size = this.blockSize * 0.45;
      this.pacman.x = Math.round(this.pacman.x / this.blockSize) * this.blockSize + this.blockSize / 2;
      this.pacman.y = Math.round(this.pacman.y / this.blockSize) * this.blockSize + this.blockSize / 2;
      this.pacman.speed = this.blockSize / 10;

      this.ghosts.forEach(ghost => {
        ghost.x = Math.round(ghost.x / this.blockSize) * this.blockSize + this.blockSize / 2;
        ghost.y = Math.round(ghost.y / this.blockSize) * this.blockSize + this.blockSize / 2;
        ghost.speed = this.blockSize / 20;
      });
    },
    initializeGameElements() {
      // 找到一个有效的起始位置给吃豆人
      for (let y = 0; y < this.map.length; y++) {
        for (let x = 0; x < this.map[y].length; x++) {
          if (this.map[y][x] === 0) {
            this.pacman.x = x * this.blockSize + this.blockSize / 2;
            this.pacman.y = y * this.blockSize + this.blockSize / 2;
            break; // 找到后立即退出循环
          }
        }
      }

      // 确保幽灵在有效位置开始
      this.ghosts.forEach(ghost => {
        let validPositionFound = false;
        while (!validPositionFound) {
          const randomX = Math.floor(Math.random() * this.map[0].length);
          const randomY = Math.floor(Math.random() * this.map.length);
          if (this.map[randomY][randomX] === 0) {
            ghost.x = randomX * this.blockSize + this.blockSize / 2;
            ghost.y = randomY * this.blockSize + this.blockSize / 2;
            validPositionFound = true;
          }
        }
      });
    },
  },
  beforeUnmount() { // 使用beforeUnmount替换beforeDestroy
    window.removeEventListener("keydown", this.handleKeydown);
    window.removeEventListener("keyup", this.handleKeyup);
    window.removeEventListener("gamepadconnected", this.handleGamepadConnected);
    window.removeEventListener("gamepaddisconnected", this.handleGamepadDisconnected);
    window.removeEventListener("resize", this.resizeCanvas);
  },
};
</script>

<style scoped>
canvas {
  display: block;
  margin: 0 auto;
  background-color: black;
}
</style>