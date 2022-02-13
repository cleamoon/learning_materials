class mainScene {
    preload() {
        // This method is called once at the beginning 
        // It will load all the assets, like sprites and sound
        this.load.image('player', 'assets/player.png');
        this.load.image('coin', 'assets/coin.png');
    }

    create() {
        // This method is called once, just after preload()
        // It will initialize our scene, like the positions of the sprites
        this.player = this.physics.add.sprite(100, 100, "player");
        this.coin = this.physics.add.sprite(300, 300, "coin");

        this.score = 0;

        let style = { font: "20px Arial", fill: "#fff"};

        this.scoreText = this.add.text(20, 20, "Score: " + this.score, style);

        this.arrow = this.input.keyboard.createCursorKeys();
    }

    update() {
        // This method is called 60 times per second after create()
        // It will handle all the game's logic, like movements
        if (this.arrow.right.isDown) {
            this.player.x += 3;
        } else if (this.arrow.left.isDown) {
            this.player.x -= 3;
        }
        if (this.arrow.down.isDown) {
            this.player.y += 3;
        } else if (this.arrow.up.isDown) {
            this.player.y -= 3;
        }

        if (this.physics.overlap(this.player, this.coin)) {
            this.hit();
        }
    }

    hit() {
        this.coin.x = Phaser.Math.Between(100, 600);
        this.coin.y = Phaser.Math.Between(100, 300);

        this.tweens.add({
            targets: this.player,   // on the player
            duration: 200,          // for 200ms
            scaleX: 1.2,            // scale vertically by 20%
            scaleY: 1.2,            // scale horizontally by 20%
            yoyo: true,             // at the end, go back to original scale
        });
        this.score += 10;
        this.scoreText.setText("Score: " + this.score);
    }
}


new Phaser.Game({
    width: 700,
    height: 400,
    backgroundColor: "#3498db", // blue
    scene: mainScene,
    physics: { default: "arcade" }, // The physics engine to use
    parent: "game",  // Create the game inside the <div id="game">
});