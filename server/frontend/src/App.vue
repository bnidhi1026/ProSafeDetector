<script setup lang="ts">
import { RouterLink, RouterView } from 'vue-router'
import HelloWorld from './components/DeviceComponent.vue'
</script>

<template>
  <n-page-header subtitle="Embedded Final Project | Group 3">
    <template #title>
      <a
          href="/"
          style="text-decoration: none; color: inherit"
      >
        Factory Controller
      </a>
    </template>
    <template #avatar>
      <n-avatar
          src="https://cdnimg103.lizhi.fm/user/2017/02/04/2583325032200238082_160x160.jpg"
      />
    </template>
  </n-page-header>

  <RouterView class="main-view"/>
</template>

<style scoped>
  .main-view {
    margin-top: 50px;
  }
</style>
