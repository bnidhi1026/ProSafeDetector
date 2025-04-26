<template>
  <n-card :title="device.name">
    <n-space vertical>
      <n-tag v-if="device.value">{{ device.value }}</n-tag>

      <n-space v-if="device.type == 'output'">
        <n-button type="primary" @click="setDeviceVal(1)">Turn On</n-button>
        <n-button type="error" @click="setDeviceVal(0)">Turn Off</n-button>
      </n-space>

    </n-space>
  </n-card>
</template>
<script setup lang="ts">
import {onMounted, ref} from "vue";
import {apiUrl} from "@/main";

const props = defineProps<{
  device: {value: number, id: number, name: string, type: "input"|"output"}
}>();

const currentDeviceVal = ref<number|null>();

const setDeviceVal = async (value : number) => {
  const response = await fetch(`${apiUrl}/devices/${props.device.name}`, {
    method: "POST",
    mode: "cors",
    headers: {
      "Content-Type": "application/json",
    },
    body: JSON.stringify({value}), // body data type must match "Content-Type" header
  });
}
</script>

<style scoped>
h1 {
  font-weight: 500;
  font-size: 2.6rem;
  position: relative;
  top: -10px;
}

h3 {
  font-size: 1.2rem;
}

.greetings h1,
.greetings h3 {
  text-align: center;
}

@media (min-width: 1024px) {
  .greetings h1,
  .greetings h3 {
    text-align: left;
  }
}
</style>
